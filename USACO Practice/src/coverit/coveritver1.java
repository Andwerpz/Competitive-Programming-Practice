//package coverit;

import java.util.*;
import java.io.*;

public class coveritver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			HashSet<Integer> notSelected = new HashSet<Integer>();
			HashSet<Integer> selected = new HashSet<Integer>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
				notSelected.add(i);
			}
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				c.get(a).add(b);
				c.get(b).add(a);
			}
			int ans = 0;
			for(int i = 0; i < n; i++) {
				if(c.get(i).size() > 1) {
					boolean isValid = false;
					for(int j = 0; j < c.get(i).size(); j++) {
						int next = c.get(i).get(j);
						if(c.get(next).size() == 1) {
							isValid = true;
							break;
						}
					}
					if(isValid) {
						ans ++;
						notSelected.remove(i);
						selected.add(i);
						for(int j = 0; j < c.get(i).size(); j++) {
							notSelected.remove(c.get(i).get(j));
						}
						break;
					}
					
				}
			}
			while(notSelected.size() != 0) {
				int cur = notSelected.iterator().next();
				int next = c.get(cur).get(0);
				for(int i = 0; i < c.get(cur).size(); i++) {
					if(notSelected.contains(c.get(cur).get(i))) {
						next = c.get(cur).get(i);
						break;
					}
				}
				notSelected.remove(next);
				selected.add(next);
				ans ++;
				for(int i = 0; i < c.get(next).size(); i++) {
					if(notSelected.contains(c.get(next).get(i))) {
						notSelected.remove(c.get(next).get(i));
					}
				}
				
			}
			fout.append(ans).append("\n");
			for(int i : selected) {
				fout.append(i + 1).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
