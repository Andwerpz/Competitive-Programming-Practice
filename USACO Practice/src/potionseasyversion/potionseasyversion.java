//package potionseasyversion;

import java.util.*;
import java.io.*;

public class potionseasyversion {
	public static void main(String[] args) throws IOException {
		
		//1526C1
		
		//first make sure to drink all the potions with values that are greater than or equal to 0. Then go from the least absolute value negative potion, and test whether you can drink it. 
		//if you can, then drink it and go on to the next smallest negative potion. Repeat until you have looked at all of the potions.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[][] potions = new long[n][2];
		long[] health = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int ans = 0;
		for(int i = 0; i < n; i++) {
			potions[i][0] = Integer.parseInt(st.nextToken());
			potions[i][1] = i;
			if(potions[i][0] >= 0) {
				health[i] += potions[i][0];
				ans ++;
			}
			health[i] += i == 0? 0 : health[i - 1];
		}
		Arrays.sort(potions, (a, b) -> -Long.compare(a[0], b[0]));
		for(int i = 0; i < n; i++) {
			if(potions[i][0] < 0) {
				boolean isValid = true;
				int index = (int) potions[i][1];
				
				for(int j = index; j < n; j++) {
					//System.out.println(health[j] + " " + potions[i][0]);
					if(health[j] < Math.abs(potions[i][0])) {
						//System.out.println("INVALID");
						isValid = false;
						break;
					}
				}
				if(isValid) {
					ans ++;
					for(int j = index; j < n; j++) {
						health[j] += potions[i][0];
					}
				}
			}
			
//			for(int j : health) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
		}
		System.out.println(ans);
	}
}
