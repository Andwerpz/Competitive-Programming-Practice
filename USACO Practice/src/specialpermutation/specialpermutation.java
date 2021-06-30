///package specialpermutation;

import java.util.*;
import java.io.*;

public class specialpermutation {
	public static void main(String[] args) throws IOException {
		
		//1352G
		
		//the whole problem is just writing special logic.
		//first, notice that for n == 2 or 3, there is no special permutation. I treat 4 and 5 as special cases, and then the special logic takes over
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			if(n <= 3) {
				fout.append("-1\n");
			}
			else if(n == 4) {
				fout.append("3 1 4 2\n");
			}
			else if(n == 5) {
				fout.append("1 3 5 2 4\n");
			}
			else {
				int pointer = 1;
				int taken = 0;
				for(int i = 0; i < n; i++) {
					fout.append(pointer).append(" ");
					if(pointer % 2 == 1 && pointer + 2 <= n) {
						pointer += 2;
					}
					else if(pointer % 2 == 1 && pointer + 2 > n) {
						if(n % 2 == 0) {
							pointer -= 3;
							fout.append(pointer).append(" ");
							taken = pointer;
							pointer += 4;
							fout.append(pointer).append(" ");
							pointer -= 2;
							i += 2;
						}
						else {
							pointer -= 3;
							fout.append(pointer).append(" ");
							taken = pointer;
							pointer += 2;
							fout.append(pointer).append(" ");
							pointer -= 4;
							i += 2;
						}
					}
					else if(pointer % 2 == 0) {
						//System.out.println("pointer is even: " + pointer + " " + i);
						pointer -= 2;
						if(pointer == taken) {
							pointer -= 2;
						}
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
