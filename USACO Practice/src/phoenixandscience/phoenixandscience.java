package phoenixandscience;

import java.util.*;
import java.io.*;

public class phoenixandscience {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			boolean[] target = new boolean[32];
			boolean[] cur = new boolean[32];
			cur[0] = true;
			for(int i = 0; i < target.length; i++) {
				if(((1 << i) | n) == n){
					target[i] = true;
				}
			}	
			int amt = 1;
			int pointer = 0;
			int mass = 1;
			StringBuilder curAns = new StringBuilder();
			int ans = 0;
			while(true) {
				ans ++;
				if(target[pointer] == cur[pointer] && cur[pointer]) {
					curAns.append(amt).append(" ");
					amt *= 2;
					pointer ++;
					
				}
			}
		}
	}
}
