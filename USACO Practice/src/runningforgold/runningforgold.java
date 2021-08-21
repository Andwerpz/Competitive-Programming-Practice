//package runningforgold;

import java.util.*;
import java.io.*;

public class runningforgold {
	
	public static boolean isSuperior(int a, int b, int[][] nums) {	//is a superior to b
		int numA = 0;
		int numB = 0;
		for(int i = 0; i < 5; i++) {
			if(nums[a][i] < nums[b][i]) {
				numA ++;
			}
		}
		if(numA >= 3) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1552B
		
		//there can only be 1 runner that is likely to win a gold medal.
		
		//we can use the following process: keep a running winner. Compare runner 1 and 2, and take the winner and compare to 3. Do this for all runners. It is guaranteed that it will
		//find the runner likely to win the gold medal, if there is one. To get rid of false positives, all you need to do is check your answer against all of the other runners.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][5];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < 5; j++) {
					nums[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			int ans = 0;
			for(int i = 1; i < n; i++) {
				if(!isSuperior(ans, i, nums)) {
					ans = i;
				}
			}
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				if(i != ans) {
					if(!isSuperior(ans, i, nums)) {
						isValid = false;
						break;
					}
				}
			}
			fout.append(isValid? ans + 1 : -1).append("\n");
		}
		System.out.print(fout);
	}
}
