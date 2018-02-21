using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ConvertMaze
{
	public class Point
	{
		public Point(int x, int y)
		{
			this.x = x;
			this.y = y;
		}

		public int x;
		public int y;

		public override string ToString()
		{
			return $"({x}, {y})";
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			byte[] imageData = null;
			int pw = 0;
			int stride = 0;
			
			using (var fileStream = new FileStream("maze.png", FileMode.Open))
			{
				var frame = BitmapFrame.Create(fileStream);
				pw = frame.PixelWidth;
				stride = pw * ((frame.Format.BitsPerPixel + 7) / 8);
				imageData = new byte[frame.PixelHeight * stride];
				frame.CopyPixels(imageData, stride, 0);
			}

			int w1 = 8;
			int w2 = 16;
			int cellCount = 601;
			int x = 0;

			int[,] mazeData = new int[cellCount, cellCount];

			for (int i = 0; i < cellCount; i++)
			{
				for (int j = 0; j < cellCount; j++)
				{
					if (imageData[x] == 0)
						mazeData[j, i] = 0;
					else
						mazeData[j, i] = 1;

					if (j % 2 == 0)
						x += w1;
					else
						x += w2;
				}

				if (i % 2 == 0)
					x += pw * 4;
				else
					x += pw * 12;
			}

			var cur_p = new Point(1, 1);
			var stack = new Stack<Point>();
			var isPathFound = true;
			var count = 0;

			do
			{
				var temp_p = new Point(cur_p.x, cur_p.y);

				int right_side = mazeData[cur_p.x + 1, cur_p.y];
				int bottom_side = mazeData[cur_p.x, cur_p.y + 1];

				if (right_side == 1 && bottom_side == 1)
				{
					if (cur_p.x <= cur_p.y)
						cur_p.x++;
					else
						cur_p.y++;
				}
				else if (right_side == 1)
					cur_p.x++;
				else if (bottom_side == 1)
					cur_p.y++;
				else if (mazeData[cur_p.x - 1, cur_p.y] == 1)
					cur_p.x--;
				else if (mazeData[cur_p.x, cur_p.y - 1] == 1)
					cur_p.y--;
				else
				{
					temp_p = null;
					if(stack.Count != 0)
					{
						cur_p = stack.Pop();
						continue;
					}
					else
					{
						isPathFound = false;
						break;
					}
				}

				mazeData[cur_p.x, cur_p.y] = 2;
				stack.Push(temp_p);

				count++;
				if (count > cellCount * cellCount)
				{
					isPathFound = false;
					break;
				}
			}
			while (cur_p.x != cellCount - 2 || cur_p.y != cellCount - 2);

			if(isPathFound)
			{
				int avg = (w1 + w2) / 2;
				Console.WriteLine(stack.Count);
				while (stack.Count != 0)
				{
					Point p = stack.Pop();
					Console.WriteLine(p);
					mazeData[p.x, p.y] = -1;

					
				}

				for (int i = 0; i < cellCount; i++)
				{
					for (int j = 0; j < cellCount; j++)
					{
						if(mazeData[j, i] == -1)
							DrawPoint(imageData, pw, avg, new Point(j, i), 1);
						if(mazeData[j,i] == 2)
							DrawPoint(imageData, pw, avg, new Point(j, i), 0);
					}
				}

				var frame = BitmapFrame.Create(pw, pw, 96, 96, PixelFormats.Bgra32, null, imageData, stride);
				PngBitmapEncoder encoder = new PngBitmapEncoder();
				encoder.Frames.Add(BitmapFrame.Create(frame));
				using (var fileStream = File.Create("maze_with_path.png"))
				{
					encoder.Save(fileStream);
				}
			}

			Console.ReadLine();
		}

		private static void DrawPoint(byte[] imageData, int pw, int avg, Point p, int shift)
		{
			int index = p.x * avg + (p.y * avg) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg - 4 + (p.y * avg - 4) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg + (p.y * avg - 4) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg + 4 + (p.y * avg - 4) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg + 4 + (p.y * avg) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg - 4 + (p.y * avg) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg + (p.y * avg + 4) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg + 4 + (p.y * avg + 4) * pw;
			imageData[index + shift] = 0;
			index = p.x * avg - 4 + (p.y * avg + 4) * pw;
			imageData[index + shift] = 0;
		}
	}
}
