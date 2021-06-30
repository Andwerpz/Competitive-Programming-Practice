//package harmoniousgraph;

import java.util.*;
import java.io.*;

public class harmoniousgraph {
	
	static StreamTokenizer fin;
	static int nextInt() throws IOException{
		fin.nextToken();
		return (int)fin.nval;
	}
	
	public static void main(String[] args) throws IOException {
		
		//sometimes, it's necessary to use fast i/o. 
		
		//we are given a simple, undirected graph. We are tasked with finding out the minimum amount of new connections required to make this graph harmonious.
		//if two nodes, i and m, can reach each other, then in order for it to be harmonious, then i must be able to reach all nodes from i - m. 
		//in order to satisfy this requirement, we have to make it so that we have a complete graph from the lowest number, to the highest number it can initially reach. 
		//it is not required that all the nodes are in one graph, just that all of them are harmonious; they don't have any gaps in numbers.  (for example, a graph with 
		//its lowest node being 10, and highest node being 100, it has to contain all nodes within 10 and 100.). We can do a simple dfs to find out the initial groupings, and 
		//then, connect them when their segments intersect. 
		
		fin = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		int n = nextInt();
		int m = nextInt();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < m; i++) {
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		HashSet<Integer> v = new HashSet<Integer>();
		Stack<Integer> s = new Stack<Integer>();
		ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			if(!v.contains(i)) {
				s.add(i);
				v.add(i);
				groups.add(new ArrayList<Integer>());
				groups.get(groups.size() - 1).add(i);
				while(s.size() != 0) {
					int next = s.pop();
					for(int j = 0; j < c.get(next).size(); j++) {
						if(!v.contains(c.get(next).get(j))) {
							s.add(c.get(next).get(j));
							v.add(c.get(next).get(j));
							groups.get(groups.size() - 1).add(c.get(next).get(j));
						}
					}
				}
				groups.get(groups.size() - 1).sort((a, b) -> Integer.compare(a, b));
			}
		}
//		for(ArrayList<Integer> i : groups) {
//			if(i.size() > 1) {
//				System.out.println(i);
//			}
//		}
		int[] sections = new int[n];
		Arrays.fill(sections, -1);
		for(int i = 0; i < groups.size(); i++) {
			int begin = groups.get(i).get(0);
			int end = groups.get(i).get(groups.get(i).size() - 1);
			sections[begin] = i;
			sections[end] = i;
			if(begin == end) {
				sections[begin] = -2;
			}
		}
		HashSet<Integer> cur = new HashSet<Integer>();
		int ans = 0;
		for(int i = 0; i < sections.length; i++) {
			if(sections[i] > -1) {
				if(cur.contains(sections[i])) {
					cur.remove(sections[i]);
				}
				else {
					
					cur.add(sections[i]);
					if(cur.size() != 1) {
						//System.out.println("ADDING 2");
						ans ++;
					}
					
				}
			}
			else if(sections[i] == -2) {
				if(cur.size() != 0) {
					ans ++;
				}
			}
		}
		System.out.println(ans);
	}
}
