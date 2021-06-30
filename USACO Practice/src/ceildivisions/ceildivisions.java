//package ceildivisions;

import java.util.*;
import java.io.*;

public class ceildivisions {
	public static void main(String[] args) throws IOException {
		
		//1469D
		
		//square roots with ceil div is so annoying :((
		
		//How we do this is we have the biggest number become 2. Since we can't make the biggest number turn into 1 in one move, we have to make it 2. We do this
		//by dividing it by it's square roots, and keep doing that, until it becomes 2.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			TreeSet<Integer> dict = new TreeSet<Integer>();
			int pointer = n;
			while(pointer > 2) {
				//System.out.println(pointer);
				dict.add(pointer);
				pointer = (int) (Math.floor(Math.sqrt(pointer)));
			}
			dict.add(2);	//pointer is 2 now
			int ans = 0;
			StringBuilder cur = new StringBuilder();
			for(int i = 2; i < n; i++) {
				if(!dict.contains(i)) {
					cur.append(i).append(" ").append(i + 1).append("\n");
					ans ++;
				}
			}
			//System.out.println(dict);
			dict.pollLast();
			int secondToLast = dict.size() == 1? n : 0;
			int prev = dict.pollLast();
			pointer = n;
			while(dict.size() != 0) {
				cur.append(n).append(" ").append(prev).append("\n");
				cur.append(prev).append(" ").append(n).append("\n");
				pointer = (int) (Math.ceil(((double) pointer) / ((double) prev)));
				ans += 2;
				if(dict.size() == 0) {
					break;
				}
				if(dict.size() == 1) {
					//System.out.println("YES");
					secondToLast = prev;
				}
				prev = dict.pollLast();
			}
			secondToLast = pointer;
			//System.out.println(secondToLast);
			while(secondToLast != 2) {
				cur.append(n).append(" ").append(prev).append("\n");
				ans += 1;
				secondToLast = (int) (Math.ceil(((double) secondToLast) / ((double) 2d)));
				//System.out.println(secondToLast);
			}
			cur.append(prev).append(" ").append(n).append("\n");
			ans ++;
			fout.append(ans).append("\n");
			fout.append(cur.toString());
		}
		System.out.print(fout);
	}
}
