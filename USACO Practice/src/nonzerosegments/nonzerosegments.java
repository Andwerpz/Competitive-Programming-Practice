//package nonzerosegments;

import java.util.*;
import java.io.*;

public class nonzerosegments {
	public static void main(String[] args) throws IOException {
		
		//1426D
		
		//don't exactly understand how i came to this answer, but whatever. Check tutorial.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		HashMap<Long, Integer> dict = new HashMap<Long, Integer>();
		int ans = 0;
		long sum = 0;
		dict.put(0l, 0);
		int low = 0;
		for(int i = 0; i < n; i++) {
			long next = Integer.parseInt(st.nextToken());
			sum += next;
			if(dict.containsKey(sum)) {
				ans ++;
				low = dict.get(sum);
				dict = new HashMap<Long, Integer>();
				dict.put(0l, 0);
				dict.put(next, i);
				sum = next;
			}
			else {
				dict.put(sum, i);
			}
		}
		System.out.println(ans);
	}
}
