//package subsetequality;

import java.util.*;
import java.io.*;

public class subsetequality {
	public static void main(String[] args) throws IOException {
		
		//2022 March USACO Silver
		
		//if a query is true, then we know that all the subsets of that query also have to be true
		
		//instead of checking whether each query is true, can we first preprocess some number of subsets
		//and use those subsets to check whether the query is true?
		
		//notice that the number of 2-character subsets is the least amount. We can't do 1 character subsets
		//since that won't give us any information.
		
		//to check a query, check whether all combinations of 2 characters you make from the query's characters
		//exist within the set of valid subsets.
		
		//a special case is where there is only 1 character in a query. It is easy to preprocess the answers for 
		//this type of query
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		int n = Integer.parseInt(fin.readLine());
		HashSet<String> set = new HashSet<>();
		for(char a = 'a'; a <= 'r'; a++) {
			for(char b = (char) (a + 1); b <= 'r'; b++) {
				ArrayList<Boolean> sc = new ArrayList<>();
				ArrayList<Boolean> tc = new ArrayList<>();
				for(int i = 0; i < s.length; i++) {
					if(s[i] == a || s[i] == b) {
						sc.add(s[i] == a);
					}
				}
				for(int i = 0; i < t.length; i++) {
					if(t[i] == a || t[i] == b) {
						tc.add(t[i] == a);
					}
				}
				if(sc.size() != tc.size()) {
					continue;
				}
				boolean isValid = true;
				for(int i = 0; i < sc.size(); i++) {
					if(sc.get(i) != tc.get(i)) {
						isValid = false;
						break;
					}
				}
				if(isValid) {
					set.add(a + "" + b);
					set.add(b + "" + a);
				}
			}
			//individual letters
			int sCnt = 0;
			int tCnt = 0;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == a) {
					sCnt ++;
				}
			}
			for(int i = 0; i < t.length; i++) {
				if(t[i] == a) {
					tCnt ++;
				}
			}
			if(sCnt == tCnt) {
				set.add(a+"");
			}
		}
		//System.out.println(set);
		StringBuilder fout = new StringBuilder();
		for(int test = 0; test < n; test++) {
			char[] q = fin.readLine().toCharArray();
			boolean isValid = true;
			outer:
			for(int i = 0; i < q.length; i++) {
				for(int j = i + 1; j < q.length; j++) {
					if(!set.contains(q[i] + "" + q[j])) {
						isValid = false;
						break outer;
					}
				}
			}
			if(q.length == 1) {
				isValid = set.contains(q[0]+"");
			}
			fout.append(isValid? "Y" : "N");
		}
		System.out.println(fout);
	}
}
