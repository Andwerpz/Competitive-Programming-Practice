package nastyaandscoreboard;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class nastyaandscoreboard {
	public static void main(String[] args) throws IOException {
		
		//1340B
		
		//hmm
		//this solution is n ^ 3, not going to work
		
		//i think i can make it n ^ 2
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		char[][] lights = new char[10][7];
		//"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"
		lights[0] = "1110111".toCharArray();
		lights[1] = "0010010".toCharArray();
		lights[2] = "1011101".toCharArray();
		lights[3] = "1011011".toCharArray();
		lights[4] = "0111010".toCharArray();
		lights[5] = "1101011".toCharArray();
		lights[6] = "1101111".toCharArray();
		lights[7] = "1010010".toCharArray();
		lights[8] = "1111111".toCharArray();
		lights[9] = "1111011".toCharArray();
		ArrayList<ArrayList<int[]>> c = new ArrayList<ArrayList<int[]>>();
		ArrayList<ArrayList<boolean[]>> v = new ArrayList<ArrayList<boolean[]>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<int[]>());
			char[] next = fin.readLine().toCharArray();
			for(int j = 0; j < 10; j ++) {
				int cost = 0;
				for(int h = 0; h < 7; h++) {
					if(next[h] == '0') {
						if(lights[j][h] == '1') {
							cost ++;
						}
					}
					else {
						if(lights[j][h] == '0') {
							cost = -1;
							break;
						}
					}
				}
				if(cost != -1) {
					c.get(i).add(new int[] {j, cost});
				}
			}
			c.get(i).sort((a, b) -> -(a[0] - b[0]));
		}
		int[][] ans = new int[n][2];	//stores which option we were on
		int pointer = 0;
		while(true) {
			while((pointer == 0? 0 + ans[pointer - 1][1]) + c.get(pointer).get(ans[pointer][0]) > k) {
				
			}
		}
	}
}
