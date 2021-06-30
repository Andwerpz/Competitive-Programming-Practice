//package readingbookseasyversion;

import java.util.*;
import java.io.*;

public class readingbookseasyversion {
	public static void main(String[] args) throws IOException {
		
		//1374E1
		
		//notice that both alice and bob need to read the same amount of books, so prioritizing books that only alice or bob likes differently isn't the solution to the problem. 
		//instead, notice that you can treat one book that alice likes, and one book that bob likes as a single book that both of them like. To generate the single books with the smallest value, 
		//get all of the books that only one of them like, and sort them in ascending order. Then start pairing them up from least to greatest. Once you're done, you're left with a list
		//of books that both of them like. to solve, pick the k books with the least time, or return -1 if there are not k books.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		PriorityQueue<Integer> both = new PriorityQueue<Integer>((f, g) -> Integer.compare(f, g));
		PriorityQueue<Integer> a = new PriorityQueue<Integer>((f, g) -> Integer.compare(f, g));
		PriorityQueue<Integer> b = new PriorityQueue<Integer>((f, g) -> Integer.compare(f, g));
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int ans = 0;
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int val = Integer.parseInt(st.nextToken());
			int aLikes = Integer.parseInt(st.nextToken());
			int bLikes = Integer.parseInt(st.nextToken());
			if(aLikes == 1 && bLikes == 1) {
				both.add(val);
			}
			else if(aLikes == 1) {
				a.add(val);
			}
			else if(bLikes == 1) {
				b.add(val);
			}
		}
		for(int i = 0; i < k; i++) {
			if(both.size() != 0 && a.size() != 0 && b.size() != 0) {
				if(both.peek() <= a.peek() + b.peek()) {
					ans += both.poll();
				}
				else {
					ans += a.poll();
					ans += b.poll();
				}
			}
			else if(both.size() != 0) {
				ans += both.poll();
			}
			else if(a.size() != 0 && b.size() != 0) {
				ans += a.poll() + b.poll();
			}
			else {
				isValid = false;
				break;
			}
			//System.out.println(ans);
		}
		if(isValid) {
			System.out.println(ans);
		}
		else {
			System.out.println("-1");
		}
	}
}
