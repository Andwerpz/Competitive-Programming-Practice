//package sashaandabitofrelax;

import java.util.*;
import java.io.*;

public class sashaandabitofrelax {
	public static void main(String[] args) throws IOException {
		
		//dammmmn, im dumb. this is pretty much just a good subarrays problem, just in disguise. 
		//we have to find 'funny' pairs, where the two halves have to equal to the same through xor. 
		//a good range will all xor to 0, the one caveat being that a range must have an odd index sum when adding the ends. 
		//this is solved by putting odd and even indexes separate in the dictionary.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] pfx = new int[n + 1];
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 1; i <= n; i++) {
			pfx[i] = pfx[i - 1] ^ nums[i - 1];
		}
		ArrayList<HashMap<Integer, Integer>> dict = new ArrayList<HashMap<Integer, Integer>>();	//index 0 is for evens, 1 is for odds.	evens go with odds and vice versa
		dict.add(new HashMap<Integer, Integer>());
		dict.add(new HashMap<Integer, Integer>());
		long ans = 0;
		for(int i = 0; i < pfx.length; i++) {
			if(dict.get(i % 2).containsKey(pfx[i])) {
				ans += dict.get(i % 2).get(pfx[i]);
			}
			dict.get(i % 2).put(pfx[i], dict.get(i % 2).getOrDefault(pfx[i], 0) + 1);
		}
		System.out.println(ans);
	}
}
