//package basicdiplomacy;

import java.util.*;
import java.io.*;

public class basicdiplomacyver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[] remaining = new int[n];
			int[] timesPicked = new int[n];
			int[][] days = new int[m][];
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int k = Integer.parseInt(st.nextToken());
				days[i] = new int[k];
				for(int j = 0; j < k; j++) {
					days[i][j] = Integer.parseInt(st.nextToken()) - 1;
					remaining[days[i][j]] ++;
				}
			}
			boolean isValid = true;
			StringBuilder cur = new StringBuilder();
			for(int i = 0; i < m; i++) {
				int minRemaining = Integer.MAX_VALUE;
				int id = 0;
				for(int j = 0; j < days[i].length; j++) {
					if(minRemaining > remaining[days[i][j]]) {
						id = days[i][j];
						minRemaining = remaining[days[i][j]];
					}
				}
				cur.append(id + 1).append(" ");
				timesPicked[id] ++;
				if(timesPicked[id] > (int) Math.ceil(m / 2)) {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				fout.append("YES\n").append(cur.toString()).append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
