//package newyearbookreading;

import java.util.*;
import java.io.*;

public class newyearbookreading {
	public static void main(String[] args) throws IOException {
		
		//500C
		
		//to make the cost minimum, arrange the books in the order they first appear. If you don't a book at all, then you put it at the bottom of the stack.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int[][] books = new int[n][2];	//cost to read, position on stack
		for(int i = 0; i < n; i++) {
			books[i][1] = n;
		}
		HashSet<Integer> seen = new HashSet<Integer>();
		int counter = 0;
		int sum = 0;
		int[] order = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			order[i] = next;
			if(!seen.contains(next)) {
				books[next][0] = sum;
				sum += nums[next];
				books[next][1] = counter;
				counter ++;
				seen.add(next);
			}
		}
		long ans = 0;
		for(int i = 0; i < m; i++) {
			int next = order[i];
			ans += books[next][0];
			
			for(int j = 0; j < n; j++) {
				if(books[j][1] < books[next][1]) {
					books[j][1] ++;
					books[j][0] += nums[next];
				}
			}books[next][1] = 0;
			books[next][0] = 0;
//			for(int[] j : books) {
//				System.out.print(j[1] + " ");
//			}
//			System.out.println();
		}
		System.out.println(ans);
	}
}
