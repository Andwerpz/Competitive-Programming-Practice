//package basicdiplomacy;

import java.util.*;
import java.io.*;

public class basicdiplomacy {
	public static void main(String[] args) throws IOException {
		
		//1482C, 1484C
		
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
			Arrays.fill(ans, -1);
			boolean isValid = true;
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int k = Integer.parseInt(st.nextToken());
				days[i] = new int[k];
				for(int j = 0; j < k; j++) {
					days[i][j] = Integer.parseInt(st.nextToken()) - 1;
				}
				if(k == 1) {
					ans[i] = days[i][0];
					timesPicked[days[i][0]] ++;
					if(timesPicked[days[i][0]] > (int) Math.ceil((double) m / 2)) {
						isValid = false;
					}
				}
			}
			if(isValid) {
				fout.append("YES\n");
				for(int i = 0; i < m; i++) {
					if(ans[i] == -1) {
						for(int j = 0; j < days[i].length; j++) {
							if(timesPicked[days[i][j]] < (int) Math.ceil((double) m / 2)) {
								timesPicked[days[i][j]] ++;
								ans[i] = days[i][j];
								break;
							}
						}
					}
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
