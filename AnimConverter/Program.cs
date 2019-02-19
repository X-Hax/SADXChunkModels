using SA_Tools;
using SonicRetro.SAModel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnimConverter
{
	class Program
	{
		static void Main(string[] args)
		{
			Queue<string> argq = new Queue<string>(args);
			string anilstfn;
			if (argq.Count > 0)
				anilstfn = argq.Dequeue();
			else
			{
				Console.Write("Anim List: ");
				anilstfn = Console.ReadLine();
			}
			string commtnfn;
			if (argq.Count > 0)
				commtnfn = argq.Dequeue();
			else
			{
				Console.Write("Common Motions: ");
				commtnfn = Console.ReadLine();
			}
			string chrmtnfn;
			if (argq.Count > 0)
				chrmtnfn = argq.Dequeue();
			else
			{
				Console.Write("Character Motions: ");
				chrmtnfn = Console.ReadLine();
			}
			string mapfn;
			if (argq.Count > 0)
				mapfn = argq.Dequeue();
			else
			{
				Console.Write("Animation Map: ");
				mapfn = Console.ReadLine();
			}
			var anilst = SA2AnimationInfoList.Load(anilstfn);
			Dictionary<int, NJS_MOTION> mtns = new Dictionary<int, NJS_MOTION>();
			ProcessMTN(commtnfn, mtns);
			ProcessMTN(chrmtnfn, mtns);
			List<int> map = IniSerializer.Deserialize<List<int>>(mapfn);
			string outdir;
			if (argq.Count > 0)
				outdir = argq.Dequeue();
			else
			{
				Console.Write("Output Directory: ");
				outdir = Console.ReadLine();
			}
			Directory.CreateDirectory(outdir);
			var outanilst = new SA2AnimationInfo[map.Count];
			for (ushort i = 0; i < map.Count; i++)
			{
				SA2AnimationInfo newinfo = new SA2AnimationInfo();
				SA2AnimationInfo oldinfo = anilst[map[i]];
				newinfo.Animation = i;
				newinfo.Model = oldinfo.Model;
				newinfo.Unknown1 = oldinfo.Unknown1;
				newinfo.Property = oldinfo.Property;
				newinfo.Unknown2 = oldinfo.Unknown2;
				newinfo.NextAnimation = (ushort)map.IndexOf(oldinfo.NextAnimation);
				newinfo.TransitionSpeed = oldinfo.TransitionSpeed;
				newinfo.AnimationSpeed = oldinfo.AnimationSpeed;
				mtns[anilst[oldinfo.Animation].Animation].Save(Path.Combine(outdir, i + ".saanim"));
				outanilst[i] = newinfo;
			}
			SA2AnimationInfoList.Save(outanilst, Path.Combine(outdir, "Animation List.ini"));
		}

		private static void ProcessMTN(string fn, Dictionary<int, NJS_MOTION> mtns)
		{
			byte[] file = File.ReadAllBytes(fn);
			if (Path.GetExtension(fn).Equals(".prs", StringComparison.OrdinalIgnoreCase))
				file = FraGag.Compression.Prs.Decompress(file);
			ByteConverter.BigEndian = file[2] == 0;
			int address = 0;
			int i = ByteConverter.ToInt16(file, address);
			while (i != -1)
			{
				int aniaddr = ByteConverter.ToInt32(file, address + 4);
				mtns[i] = new NJS_MOTION(file, aniaddr, 0, ByteConverter.ToInt16(file, address + 2));
				address += 8;
				i = ByteConverter.ToInt16(file, address);
			}
		}
	}
}
