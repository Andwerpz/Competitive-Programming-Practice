//package connectingtwobarns;

import java.util.*;
import java.io.*;

public class connectingtwobarns {
	
	static StreamTokenizer in;
	static int nextInt() throws IOException {
		in.nextToken();
		return (int) in.nval;
	}

	public static void main(String[] args) throws IOException {
		
		//USACO 2021 December Contest Silver
		
		//graphs. idk why this one is timing out
		
		//BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		int t = nextInt();
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = nextInt();
			int m = nextInt();
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < m; i++) {
				//st = new StringTokenizer(fin.readLine());
				int a = nextInt() - 1;
				int b = nextInt() - 1;
				c.get(a).add(b);
				c.get(b).add(a);
			}
			ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
			boolean[] v = new boolean[n];
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					ArrayList<Integer> curGroup = new ArrayList<Integer>();
					Stack<Integer> s = new Stack<Integer>();
					s.add(i);
					v[i] = true;
					while(s.size() != 0) {
						int cur = s.pop();
						curGroup.add(cur);
						for(int a : c.get(cur)) {
							if(!v[a]) {
								v[a] = true;
								s.add(a);
							}
						}
					}
					groups.add(curGroup);
				}
			}
			
			int hasStart = 0;
			int hasEnd = 0;
			for(int i = 0; i < groups.size(); i++) {
				for(int j : groups.get(i)) {
					if(j == 0) {
						hasStart = i;
					}
					if(j == n - 1) {
						hasEnd = i;
					}
				}
			}
			if(hasStart == hasEnd) {
				fout.append("0\n");
				continue;
			}
			for(int i = 0; i < groups.size(); i++) {
				groups.get(i).sort((a, b) -> Integer.compare(a, b));
			}
			//System.out.println(groups);
			long[] fromStart = new long[groups.size()];
			long[] toEnd = new long[groups.size()];
			for(int i = 0; i < groups.size(); i++) {
				int a = 0;
				int b = 0;
				int minDiff = Integer.MAX_VALUE;
				while(true) {
					//System.out.println(a + " " + b);
					int aVal = groups.get(hasStart).get(a);
					int bVal = groups.get(i).get(b);
					//System.out.println(aVal + " " + bVal);
					minDiff = Math.min(minDiff, Math.abs(aVal - bVal));
					if(minDiff == 0 || minDiff == 1) {
						break;
					}
					if(aVal < bVal) {
						a++;
					}
					else {
						b++;
					}
					if(a > groups.get(hasStart).size() || b > groups.get(i).size()) {
						break;
					}
				}
				fromStart[i] = minDiff;
			}
			for(int i = 0; i < groups.size(); i++) {
				int a = 0;
				int b = 0;
				int minDiff = Integer.MAX_VALUE;
				while(true) {
					int aVal = groups.get(hasEnd).get(a);
					int bVal = groups.get(i).get(b);
					minDiff = Math.min(minDiff, Math.abs(aVal - bVal));
					if(minDiff == 0 || minDiff == 1) {
						break;
					}
					if(aVal < bVal) {
						a++;
					}
					else {
						b++;
					}
					if(a > groups.get(hasEnd).size() || b > groups.get(i).size()) {
						break;
					}
				}
				toEnd[i] = minDiff;
			}
			long ans = Long.MAX_VALUE;
			for(int i = 0; i < groups.size(); i++) {
				ans = (long) Math.min(ans, Math.pow(fromStart[i], 2l) + Math.pow(toEnd[i], 2l));
			}
			fout.append(ans).append("\n");
			
			
		}
		System.out.print(fout);
	}
}
