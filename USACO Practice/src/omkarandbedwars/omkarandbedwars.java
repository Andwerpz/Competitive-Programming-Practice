package omkarandbedwars;

import java.util.*;
import java.io.*;

public class omkarandbedwars {
	public static void main(String[] args) throws IOException {
		
		//1392D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			ArrayList<int[]> groups = new ArrayList<int[]>();
			char[] s = fin.readLine().toCharArray();
			int start = 0;
			boolean seenLeft = false;
			boolean seenRight = false;
			int pointer = 0;
			boolean curRight = false;
			int counter = 0;
			boolean allOne = true;
			int prev = s[0];
			for(int i = 0; i < n; i++) {
				if(s[i] != prev) {
					allOne = false;
					break;
				}
			}
			while(!allOne && true) {
				char next = s[pointer % n];
				//System.out.print(pointer + " " + next + " ");
				if(!seenLeft || !seenRight) {
					if(next == 'L') {
						seenLeft = true;
					}
					else if(next == 'R' && seenLeft) {
						//System.out.print("start");
						start = pointer;
						seenRight = true;
						curRight = true;
						groups.add(new int[] {0, 0});
						counter ++;
					}
				}
				else {
					if(curRight) {
						if(next == 'R') {
							counter ++;
						}
						else {
							groups.get(groups.size() - 1)[0] = counter;
							counter = 1;
							curRight = false;
						}
					}
					else {
						if(next == 'L') {
							counter ++;
						}
						else {
							groups.get(groups.size() - 1)[1] = counter;
							counter = 1;
							if(pointer % n == start % n) {
								break;
							}
							groups.add(new int[] {0, 0});
							curRight = true;
						}
					}
				}
				pointer ++;
				
			}
//			System.out.println();
			for(int[] i : groups) {
				System.out.println(i[0] + " " + i[1]);
			}
			System.out.println();
			int ans = 0;
			if(allOne) {
				ans = n / 3 + (n % 3 != 0? 1 : 0);
			}
			else {
				for(int i = 0; i < groups.size(); i++) {
					int cur = (groups.get(i)[0] - 1) / 3 + (groups.get(i)[0] - 1 % 3 != 0? 1 : 0) + (groups.get(i)[1] - 1) / 3 + (groups.get(i)[1] - 1 % 3 != 0? 1 : 0);
					if(groups.get(i)[0] >= 2) {
						cur = Math.min(cur, (groups.get(i)[0] - 3) / 3 + (groups.get(i)[0] % 3 != 0? 1 : 0) + (groups.get(i)[1] - 1) / 3 + (groups.get(i)[1] - 1 % 3 != 0? 1 : 0) + 1);
					}
					if(groups.get(i)[1] >= 2) {
						cur = Math.min(cur, (groups.get(i)[0] - 1) / 3 + (groups.get(i)[0] - 1 % 3 != 0? 1 : 0) + (groups.get(i)[1] - 3) / 3 + (groups.get(i)[1] % 3 != 0? 1 : 0) + 1);
					}
					System.out.println("CUR: " + cur + " " + i);
					ans += cur == -1? 0 : cur;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
