//package taskontheboard;

import java.util.*;
import java.io.*;

public class taskontheboard {
	public static void main(String[] args) throws IOException {
		
		//1367D
		
		//to do this one, first you have to figure out which letters in the final result are greater than the other letters. Obviously, you can start with the ones of value 0. Those
		//have to be the greatest. You can use those to find the second greatest, and then using the combination of the first and second greatest, find the third greatest, and so on.
		
		//after that, since a solution is guaranteed, you just have to match the ids with the letters, and you're done.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int m = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[m];
			int[] id = new int[m];
			Arrays.fill(id, -1);
			for(int i = 0; i < m; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int counter = 0;
			while(true) {
				boolean done = true;
				for(int i = 0; i < m; i++) {
					if(id[i] == -1) {
						done = false;
						int diff = 0;
						for(int j = 0; j < m; j++) {
							if(id[j] < counter && id[j] != -1) {
								diff += Math.abs(i - j);
							}
						}
						if(diff == nums[i]) {
							id[i] = counter;
						}
					}
				}
				if(done) {
					break;
				}
				counter ++;
			}
			for(int i = 0; i < id.length; i++) {
				id[i] = counter - id[i] - 1;
			}
			int[] charGroups = new int[26];
			for(int i = 0; i < s.length; i++) {
				int next = s[i] - 'a';
				charGroups[next] ++;
			}
			int[] idGroups = new int[counter];
			for(int i = 0; i < id.length; i++) {
				idGroups[id[i]] ++;
			}
			char[] ans = new char[id.length];
			int pointer = 0;
			for(int i = 0; i < idGroups.length; i++) {
				int curAmt = idGroups[i];
				while(charGroups[pointer] < curAmt) {
					pointer ++;
				}
				for(int j = 0; j < id.length; j++) {
					if(id[j] == i) {
						ans[j] = (char) (pointer + 'a');
					}
				}
				pointer ++;
			}
			fout.append(String.valueOf(ans)).append("\n");
		}
		System.out.print(fout);
	}
}
