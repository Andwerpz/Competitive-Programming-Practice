//package palindromicmatrix;

import java.util.*;
import java.io.*;

public class palindromicmatrix {
	
	public static int getOver(int[] dict, int val) {
		int min = -1;
		int minId = -1;
		for(int i = 0; i < dict.length; i++) {
			if(dict[i] >= val) {
				if(min == -1) {
					min = dict[i];
					minId = i;
				}
				else if(min > dict[i]) {
					min = dict[i];
					minId = i;
				}
			}
		}
		return minId;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1118C
		
		//just fill in the array. When choosing the type of number to fill in, pick the number with the smallest valid amount to fill the space.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] dict = new int[1001];
		int[][] ans = new int[n][n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n * n; i++) {
			int next = Integer.parseInt(st.nextToken());
			dict[next] ++;
		}
		boolean isValid = true;
		outer:
		for(int i = 0; i < n / 2 + (n % 2 == 1? 1 : 0); i++) {
			for(int j = i; j < n / 2 + (n % 2 == 1? 1 : 0); j++) {
				//System.out.println(i + " " + j);
				int next = 0;
				int amt = 0;
				if(j == i) {
					if(j == n / 2 + (n % 2 == 1? 1 : 0) - 1) {
						if(n % 2 == 0) {
							next = getOver(dict, 4);
							amt = 4;
						}
						else {
							next = getOver(dict, 1);
							amt = 1;
						}
					}
					else {
						next = getOver(dict, 4);
						amt = 4;
					}
				}
				else if(j == n / 2 + (n % 2 == 1? 1 : 0) - 1 && n % 2 == 1){
					next = getOver(dict, 2);
					amt = 2;
				}
				else {
					next = getOver(dict, 4);
					amt = 4;
				}
				//System.out.println(amt);
				if(next == -1) {
					isValid = false;
					break outer;
				}
				else {
					dict[next] -= amt;
				}
				ans[i][j] = next;
				ans[i][n - 1 - j] = next;
				ans[n - 1 - i][j] = next;
				ans[n - 1 - i][n - 1 - j] = next;
				next = 0;
				amt = 0;
				if(j == i) {
					if(j == n / 2 + (n % 2 == 1? 1 : 0) - 1) {
						if(n % 2 == 0) {
							continue;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				else if(j == n / 2 + (n % 2 == 1? 1 : 0) - 1 && n % 2 == 1){
					next = getOver(dict, 2);
					amt = 2;
				}
				else {
					next = getOver(dict, 4);
					amt = 4;
				}
				//System.out.println(amt);
				if(next == -1) {
					isValid = false;
					break outer;
				}
				else {
					dict[next] -= amt;
				}
				ans[j][i] = next;
				ans[j][n - 1 - i] = next;
				ans[n - 1 - j][i] = next;
				ans[n - 1 - j][n - 1 - i] = next;
				//System.out.println(i + " " + j);
			}
		}
//		for(int i : dict) {
//			System.out.print(i + " ");
//		}
		if(isValid) {
			StringBuilder fout = new StringBuilder();
			fout.append("YES\n");
			for(int[] i : ans) {
				for(int j : i) {
					fout.append(j).append(" ");
				}
				fout.append("\n");
			}
			System.out.print(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
