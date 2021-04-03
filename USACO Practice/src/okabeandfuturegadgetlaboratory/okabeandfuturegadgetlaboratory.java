//package okabeandfuturegadgetlaboratory;

import java.util.*;
import java.io.*;

public class okabeandfuturegadgetlaboratory {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] lab = new int[n][n];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < n; j++) {
				lab[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		boolean ans = true;
		for(int x = 0; x < n; x++) {
			for(int y = 0; y < n; y++) {
				if(lab[x][y] != 1) {
					int cur = lab[x][y];
					boolean isValid = false;
					for(int i = 0; i < n; i++) {
						for(int j = 0; j < n; j++) {
							if(lab[x][i] + lab[j][y] == cur) {
								isValid = true;
								break;
							}
						}
						if(isValid) {
							break;
						}
					}
					if(!isValid) {
						ans = false;
						break;
					}
				}
				
			}
			if(!ans) {
				break;
			}
		}
		System.out.println(ans? "Yes" : "No");
	}
}
