package distinctcharactersqueries;

import java.util.*;
import java.io.*;

public class distinctcharactersqueriesver2 {
	public static void main(String[] args) throws IOException {
		
		//1234D
		
				//instead of using segment tree, there is a much faster and easier way to think about it. 
				//since you can only have 26 distinct values, it is much easier to just keep track for each value, where they show up in the string.
				
				//to keep track of this, all you have to do is to keep a tree set for each character. When you want to replace a character, just remove the position entry from the 
				//original character, and add it to the new character. When querying, just get the floor value of the high range. If the returned value is higher than the low range, 
				//then this character is within the range.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		ArrayList<TreeSet<Integer>> dict = new ArrayList<TreeSet<Integer>>();
		for(int i = 0; i < 26; i++) {
			dict.add(new TreeSet<Integer>());
		}
		for(int i = 0; i < n; i++) {
			int next = s[i] - 'a';
			dict.get(next).add(i);
		}
		StringBuilder fout = new StringBuilder();
		int q = Integer.parseInt(fin.readLine());
		for(int i = 0; i < q; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int type = Integer.parseInt(st.nextToken());
			if(type == 1) {
				int pos = Integer.parseInt(st.nextToken()) - 1;
				char val = st.nextToken().charAt(0);
				int c = val - 'a';
				int replace = s[pos] - 'a';
				s[pos] = val;
				dict.get(replace).remove(pos);
				dict.get(c).add(pos);
//				System.out.println("REPLACE: " + val + " " + (char) (replace + 'a'));
//				System.out.println(String.valueOf(s));
//				System.out.println(dict);
			}
			else {
				int low = Integer.parseInt(st.nextToken()) - 1;
				int high = Integer.parseInt(st.nextToken()) - 1;
				int ans = 0;
				for(int j = 0; j < dict.size(); j++) {
					int next = -1;
					if(dict.get(j).floor(high) != null) {
						next = dict.get(j).floor(high);
					}
					//System.out.print(next + " ");
					if(next >= low) {
						ans ++;
					}
				}
				//System.out.println();
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
