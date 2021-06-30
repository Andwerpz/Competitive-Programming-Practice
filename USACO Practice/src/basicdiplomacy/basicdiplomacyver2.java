package basicdiplomacy;

import java.util.*;
import java.io.*;

public class basicdiplomacyver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] days = new int[m][];
			int[] ans = new int[m];
			int[] timesPicked = new int[n];
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int k = Integer.parseInt(st.nextToken());
				days[i] = new int[k];
				for(int j = 0; j < k; j++) {
					days[i][j] = Integer.parseInt(st.nextToken()) - 1;
					if(j == 0) {
						ans[i] = days[i][j];
						timesPicked[days[i][j]] ++;
					}
				}
			}
			int maxPicked = 0;
			int id = 0;
			for(int i = 0; i < n; i++) {
				if(maxPicked < timesPicked[i]) {
					maxPicked = timesPicked[i];
					id = i;
				}
			}
			for(int i = 0; i < m; i++) {
				if(ans[i] == id) {
					for(int j = 0; j < days[i].length; j++) {
						if(days[i][j] != id) {
							maxPicked --;
							ans[i] = days[i][j];
							break;
						}
					}
				}
				if(maxPicked <= (int) Math.ceil(m / 2)) {
					break;
				}
			}
			if(maxPicked <= (int) Math.ceil(m / 2)) {
				fout.append("YES\n");
				for(int i = 0; i < m; i++) {
					fout.append(ans[i] + 1).append(" ");
				}
				fout.append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
