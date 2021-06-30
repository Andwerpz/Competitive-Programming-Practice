//package vasyaandmultisets;

import java.util.*;
import java.io.*;

public class vasyaandmultisets {
	public static void main(String[] args) throws IOException {
		
		//this one is really easy.
		//the key observation is that there are three different situations. Either a number is unique, a number is in a pair, or it is in a group of three or more. 
		//if the number is unique, then it will change the amount of nice numbers in the set you add it in, (changing the amount means changing the difference,
		//we want different to be equal to 0.) If a number is in a pair, then it doesn't matter how you divide it, it won't make a difference. If it is in a group of three or greater,
		//then it has a choice whether or not it wants to make a difference. If you add it all to one set, then it doesn't, but if you add one to one set, and the rest to the other set, then it does. 
		//all you have to do is determine the amount of "forced difference". If the amount of unique number is even, then forced difference is 0, and you can make
		//two sets, but if the amount is odd, then the "forced difference" is equal to one. In that case, if you have a group of three or greater, then 
		//you can offset this forced difference and make the two sets good again, if you don't then there is no way you can partition it into two sets.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		HashMap<Integer, Integer> sets = new HashMap<Integer, Integer>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sets.put(nums[i], sets.getOrDefault(nums[i], 0) + 1);
		}
		int numOnes = 0;
		boolean threeExists = false;
		for(int k : sets.keySet()) {
			if(sets.get(k) == 1) {
				numOnes ++;
			}
			else if(sets.get(k) >= 3) {
				threeExists = true;
			}
		}
		if(numOnes % 2 == 0 || (numOnes % 2 == 1 && threeExists)) {
			System.out.println("YES");
			StringBuilder fout = new StringBuilder();
			//put everything into A, except for the single digits into B
			int quota = numOnes / 2;
			boolean needExtra = (quota * 2 != numOnes);
			for(int i = 0; i < n; i++) {
				int next = sets.get(nums[i]);
				if(next >= 3 && needExtra) {
					needExtra = false;
					fout.append("B");
				}
				else if(next == 1 && quota != 0) {
					fout.append("B");
					quota --;
				}
				else {
					fout.append("A");
				}
			}
			System.out.println(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
