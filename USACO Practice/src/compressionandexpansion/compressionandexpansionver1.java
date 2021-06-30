//package compressionandexpansion;

import java.util.*;
import java.io.*;

public class compressionandexpansionver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int pointer = 0;
			int[] dict = new int[1000];
			String cur = "1";
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(fin.readLine());
				if(i == 0) {
					fout.append(next).append("\n");
					dict[0] = next;
				}
				else {
					if(next == 1) {
						pointer ++;
						dict[pointer] = next;
						cur += ".1";
						fout.append(cur).append("\n");
					}
					else {
						int amtDescended = 0;
						while(dict[pointer] + 1 != next) {
							pointer --;
							amtDescended ++;
						}
						//System.out.println(amtDescended);
						cur = cur.substring(0, cur.length() - (amtDescended * 2 + ((next - 1) + "").length())) + next;
						fout.append(cur).append("\n");
						dict[pointer] = next;
					}
				}
				//System.out.println(cur);
			}
		}
		System.out.print(fout);
	}
}
