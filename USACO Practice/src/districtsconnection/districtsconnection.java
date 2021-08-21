//package districtsconnection;

import java.util.*;
import java.io.*;

public class districtsconnection {
	public static void main(String[] args) throws IOException {
		
		//1433D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			boolean[] v = new boolean[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Stack<Integer> s = new Stack<Integer>();
			s.add(0);
			v[0] = true;
			ArrayList<int[]> c = new ArrayList<int[]>();
			while(s.size() != 0) {
				int cur = s.pop();
				int curGang = nums[cur];
				for(int i = 0; i < n; i++) {
					if(!v[i] && curGang != nums[i]) {
						c.add(new int[] {cur + 1, i + 1});
						s.add(i);
						v[i] = true;
					}
				}
			}
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				fout.append("YES\n");
				for(int[] i : c) {
					fout.append(i[0]).append(" ").append(i[1]).append("\n");
				}
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
