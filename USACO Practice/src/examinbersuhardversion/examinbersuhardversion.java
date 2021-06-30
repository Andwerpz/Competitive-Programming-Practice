//package examinbersuhardversion;

import java.util.*;
import java.io.*;

public class examinbersuhardversion {
	public static void main(String[] args) throws IOException {
		
		//1185C2
		
		//this is a pfx problem. You can solve each person in order from left to right. When failing people, always fail the people starting from the ones that take the most time.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int sum = 0;
		int counter = 0;
		PriorityQueue<Integer> pass = new PriorityQueue<Integer>((a, b) -> -(a - b));
		PriorityQueue<Integer> fail = new PriorityQueue<Integer>();
		st = new StringTokenizer(fin.readLine());
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			while(fail.peek() != null && pass.peek() > fail.peek()) {
				int a = fail.poll();
				int b = pass.poll();
				fail.add(b);
				pass.add(a);
				sum += a;
				sum -= b;
			}
			
			while(m - sum - next < 0) {
				int a = pass.poll();
				fail.add(a);
				sum -= a;
				counter ++;
			}
			while(fail.peek() != null && m - sum - next - fail.peek() >= 0) {
				int a = fail.poll();
				pass.add(a);
				sum += a;
				counter --;
			}
			//System.out.println(pass.toString() + " " + next + "\n" + fail.toString());
			pass.add(next);
			sum += next;
			fout.append(counter).append(" ");
		}
		System.out.println(fout);
	}
}
