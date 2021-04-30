//package divisibilityby8;

import java.util.*;
import java.io.*;

public class divisibilityby8ver3 {
	public static void main(String[] args) throws IOException {
		
		//precalculate all the answers, and just go through the array to check whether one answer exists
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
		}
		int pointer = 8;
		ArrayList<ArrayList<Integer>> twoDig = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> threeDig = new ArrayList<ArrayList<Integer>>();
		while(pointer < 100) {
			pointer += 8;
			String next = pointer + "";
			twoDig.add(new ArrayList<Integer>());
			twoDig.get(twoDig.size() - 1).add(Integer.parseInt(next.charAt(0) + ""));
			twoDig.get(twoDig.size() - 1).add(Integer.parseInt(next.charAt(1) + ""));
		}
		while(pointer < 1000) {
			pointer += 8;
			String next = pointer + "";
			threeDig.add(new ArrayList<Integer>());
			threeDig.get(threeDig.size() - 1).add(Integer.parseInt(next.charAt(0) + ""));
			threeDig.get(threeDig.size() - 1).add(Integer.parseInt(next.charAt(1) + ""));
			threeDig.get(threeDig.size() - 1).add(Integer.parseInt(next.charAt(2) + ""));
		}
		boolean isValid = false;
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			for(int j = 0; j < twoDig.size(); j++) {
				if(twoDig.get(j).get(0) >= 10) {
					if(twoDig.get(j).get(1) == next) {
						isValid = true;
						ans = twoDig.get(j).get(0) + twoDig.get(j).get(1);
					}
				}
				else if(twoDig.get(j).get(0) == next){
					twoDig.get(j).set(0, next * 10);
				}
			}
			for(int j = 0; j < threeDig.size(); j++) {
				if(threeDig.get(j).get(0) >= 10) {
					if(threeDig.get(j).get(1) >= 10) {
						if(threeDig.get(j).get(2) == next) {
							isValid = true;
							ans = threeDig.get(j).get(0) + threeDig.get(j).get(1) + threeDig.get(j).get(2);
						}
					}
					else if(threeDig.get(j).get(1) == next) {
						threeDig.get(j).set(1, next * 10);
					}
				}
				else if(threeDig.get(j).get(0) == next){
					threeDig.get(j).set(0, next * 100);
				}
			}
			if(next == 8 || next == 0) {
				isValid = true;
				ans = next;
			}
		}
		if(isValid) {
			System.out.println("YES\n" + ans);
		}
		else {
			System.out.println("NO");
		}
	}
}
