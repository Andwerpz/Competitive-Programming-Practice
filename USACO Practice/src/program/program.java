//package program;

import java.util.*;
import java.io.*;

public class program {
	public static void main(String[] args) throws IOException {
		
		//1473D
		
		//since we only delete from range l - r inclusive, we can just construct a pfx and sfx sum containing the range for each pfx and sfx. Then when we delete, we just add the
		//ranges pfx[l - 1] and sfx[r + 1]. We do have to adjust for the pfx end point, so for each position, we also save the current x value.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0 ) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] pfxRange = new int[n + 1][2];	//min, max
			int[][] sfxRange = new int[n + 1][2];
			int[] nums = new int[n + 1];
			char[] s = fin.readLine().toCharArray();
			//System.out.println("PREFIX:");
			for(int i = 0; i < n; i++) {
				nums[i + 1] = nums[i] + (s[i] == '+'? 1 : -1);
				pfxRange[i + 1][0] = Math.min(pfxRange[i][0], nums[i + 1]);
				pfxRange[i + 1][1] = Math.max(pfxRange[i][1], nums[i + 1]);
				//System.out.println(pfxRange[i + 1][0] + " " + pfxRange[i + 1][1]);
				//System.out.println(nums[i + 1] + " " + s[i] + " " + (s[i] == '+'? 1 : -1));
			}
			sfxRange[n][0] = nums[n];
			sfxRange[n][1] = nums[n];
			//System.out.println("SUFFIX:");
			for(int i = n; i > 0; i--) {
				sfxRange[i - 1][0] = Math.min(sfxRange[i][0], nums[i - 1]);
				sfxRange[i - 1][1] = Math.max(sfxRange[i][1], nums[i - 1]);
				//System.out.println(sfxRange[i - 1][0] + " " + sfxRange[i - 1][1]);
			}
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int l = Integer.parseInt(st.nextToken()) - 1;
				int r = Integer.parseInt(st.nextToken());
				if(l == 0 && r == n) {
					fout.append("1\n");
				}
				else if(l == 0) {
					fout.append(sfxRange[r][1] - sfxRange[r][0] + 1).append("\n");
				}
				else if(r == n) {
					//System.out.println(pfxRange[l][0] + " " + pfxRange[l][1]);
					fout.append(pfxRange[l][1] - pfxRange[l][0] + 1).append("\n");
				}
				else {
					int diff = nums[l] - nums[r];
					int low = Math.min(pfxRange[l][0], sfxRange[r][0] + diff);
					int high = Math.max(pfxRange[l][1], sfxRange[r][1] + diff);
					fout.append(high - low + 1).append("\n");
				}
			}
		}
		System.out.print(fout);
	}
}
