//package phoenixandtowers;

import java.util.*;
import java.io.*;

public class phoenixandtowers {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			PriorityQueue<Tower> q = new PriorityQueue<Tower>((a, b) -> Comparator.compareTower(a, b));
			for(int i = 0; i < m; i++) {
				q.add(new Tower(0, i + 1));
			}
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				Tower next = q.poll();
				fout.append(next.id).append(" ");
				next.height += nums[i];
				q.add(next);
				//System.out.println(q);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
	
	static class Comparator {
		
		public static int compareTower(Tower a, Tower b) {
			return Integer.compare(a.height, b.height);
		}
		
	}
	
}
class Tower {
		
		public int height;
		public int id;
		
		public Tower(int height, int id) {
			this.height = height;
			this.id = id;
		}
		
		public String toString() {
			return "ID: " + id + " HEIGHT: " + height;
		}
		
}