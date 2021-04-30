//package dashaandpassword;

import java.util.*;
import java.io.*;

public class dashaandpassword {
	public static void main(String[] args) throws IOException {
		
		//each password needs 1 digit, 1 letter and 1 special character: '*' '#' '&'
		//for each string, there are only three important properties, the first occurrence of a digit, letter, and special character.
		//if we get all the properties, and categorize them by type, digit, letter or special, and sort them by amount of moves,
		//we can just brute force all combinations, prioritizing each in turn.
		//only need 3 ^ 3 tests, 27.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		char[][] s = new char[n][m];
		for(int i = 0; i < n; i++) {
			s[i] = fin.readLine().toCharArray();
		}
		int[][][] order = new int[3][n][2];	//order[i][j][k], ith type: digit, letter, special, jth string, sorted in ascending order, k = 0: cost, k = 1: id
		for(int i = 0; i < n; i++) {
			boolean digit = false;
			boolean letter = false;
			boolean special = false;
			order[0][i][0] = Integer.MAX_VALUE;
			order[1][i][0] = Integer.MAX_VALUE;
			order[2][i][0] = Integer.MAX_VALUE;
			for(int j = 0; j < m; j++) {
				
				if(Character.isDigit(s[i][j])) {
					order[0][i][0] = Math.min(Math.min(m - j, j), order[0][i][0]);
					order[0][i][1] = i;
					//digit = true;
				}
				else if(Character.isLetter(s[i][j]) && !Character.isDigit(s[i][j])) {
					order[1][i][0] = Math.min(Math.min(m - j, j), order[1][i][0]);
					order[1][i][1] = i;
					//letter = true;
				}
				else if(!special){
					order[2][i][0] = Math.min(Math.min(m - j, j), order[2][i][0]);
					order[2][i][1] = i;
					//special = true;
				}
			}
		}
		for(int[][] i : order) {
			for(int[] j : i) {
				////System.out.println(j[0] + " " + j[1]);
			}
			////System.out.println();
		}
		Arrays.sort(order[0], (a, b) -> a[0] - b[0]);
		Arrays.sort(order[1], (a, b) -> a[0] - b[0]);
		Arrays.sort(order[2], (a, b) -> a[0] - b[0]);
		
		for(int[][] i : order) {
			for(int[] j : i) {
				//System.out.println(j[0] + " " + j[1]);
			}
			//System.out.println();
		}
		int ans = -1;
		boolean isValid = false;
		for(int i = 0; i < 3; i++) {
			HashSet<Integer> taken = new HashSet<Integer>();
			int sum = 0;
			taken.add(order[i][0][1]);
			sum += order[i][0][0];
			if(sum == Integer.MAX_VALUE) {
				continue;
			}
			for(int j = 0; j < 3; j++) {
				if(j != i) {
					HashSet<Integer> taken2 = new HashSet<Integer>();
					taken2.addAll(taken);
					int pointer = 0;
					while(pointer < n && taken2.contains(order[j][pointer][1])) {
						pointer ++;
					}
					if(pointer == n || order[j][pointer][0] == Integer.MAX_VALUE) {
						continue;
					}
					sum += order[j][pointer][0];
					taken2.add(order[j][pointer][1]);
					for(int k = 0; k < 3; k++) {
						
						if(k != i && k != j) {
							//System.out.println(i + " " + j + " " + k);
							HashSet<Integer> taken3 = new HashSet<Integer>();
							taken3.addAll(taken2);
							pointer = 0;
							while(pointer < n && taken2.contains(order[k][pointer][1])) {
								pointer ++;
							}
							
							if(pointer == n || order[j][pointer][0] == Integer.MAX_VALUE) {
								break;
							}//taken3.add(order[k][pointer][1]);
							sum += order[k][pointer][0];
							if(ans == -1 || ans > sum) {
								//System.out.println(taken3);
								ans = sum;
								isValid = true;
							}
						}
					}
				}
				
			}
			
		}
		System.out.println(ans);
	}
}
