//package standardfree2play;

import java.util.*;
import java.io.*;

public class standardfree2play {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int h = Integer.parseInt(st.nextToken());
			int n = Integer.parseInt(st.nextToken());
			int prev = h + 2;
			ArrayList<Integer> segments = new ArrayList<Integer>();
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				//System.out.println(prev + " " + next);
				if(next + 1 != prev) {
					segments.add(1);
				}
				else {
					segments.set(segments.size() - 1, segments.get(segments.size() - 1) + 1);
				}
				prev = next;
				if(next == 1) {
					segments.remove(segments.size() - 1);
				}
			}
			int ans = 0;
			for(int i = 0; i < segments.size(); i++) {
				if(i == 0) {
					if(segments.get(i) % 2 == 0) {
						ans ++;
					}
				}
				else {
					if(segments.get(i) % 2 == 1) {
						ans ++;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
