//package zookeeperandtheinfinitezoo;

import java.util.*;
import java.io.*;

public class zookeeperandtheinfinitezoo {
	public static void main(String[] args) throws IOException {
		
		//1491D
		
		//you can only make an edge from node a to a + b if a & b == b. This means that b must be entirely contained within a, so any bits that b has, a also has. 
		//This leads to an effect where the bits in the starting node, u, have to 'bubble up' to get to the destination node bits, v. So, if there exists a bit in node v,
		//in order to be valid, there needs to exist a corresponding bit in node u that is less than or equal to the bit in node v.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int u = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			Stack<Integer> start = new Stack<Integer>();
			Stack<Integer> end = new Stack<Integer>();
			int pointer = 1;
			while(pointer * 2 <= u || pointer * 2 <= v) {
				pointer *= 2;
			}
			while(pointer != 0) {
				if(pointer <= u) {
					u -= pointer;
					start.add(pointer);
				}
				if(pointer <= v) {
					v -= pointer;
					end.add(pointer);
				}
				pointer /= 2;
			}
			//System.out.println(start + "\n" + end);
			int extra = 0;
			boolean isValid = true;
			while(end.size() != 0) {
				int curEnd = end.pop();
				boolean taken = false;
				while(start.size() != 0 && start.peek() <= curEnd) {
					if(taken && start.peek() == curEnd) {
						break;
					}
					else if(taken) {
						extra ++;
					}
					start.pop();
					taken = true;
				}
				if(!taken) {
					if(extra == 0) {
						//System.out.println("FALSE");
						isValid = false;
						break;
					}
					else {
						extra --;
					}
				}
			}
			if(start.size() != 0 || !isValid) {
				fout.append("NO\n");
			}
			else {
				fout.append("YES\n");
			}
		}
		System.out.print(fout);
	}
}
