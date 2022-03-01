//package anonymityisimportant;

import java.util.*;
import java.io.*;

public class anonymityisimportant {
	
	public static void insert(int[][] tree, int index, int val) {
		tree[0][index] = Math.min(val, tree[0][index]);
		index /= 2;
		for(int i = 1; i < tree.length; i++) {
			tree[i][index] = Math.min(tree[i][index], val);
			index /= 2;
		}
	}
	
	public static int query(int[][] tree, int l, int r) {	//range min, l - r inclusive
		int ans = tree[0][l];
		for(int i = l; i <= r; i += 0) {
			int increment = 1;
			int index = i;
			int layer = 0;
			while(true) {
				int temp = index / 2;
				increment *= 2;
				layer ++;
				if(temp * increment < l || temp * increment + increment > r) {
					increment /= 2;
					layer --;
					break;
				}
				index = temp;
			}
			ans = Math.min(ans, tree[layer][index]);
			i += increment;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1642E
		
		//notice that if a patient is within a range declared not sick, then they can never be sick. Let's call these patients immune
		
		//also notice that in order to know if a patient is sick, it needs to be true there exists a query of type x = 1, where they are the only
		//one not immune within the range, l - r.
		
		//first, we can keep a set of non-immune patients, 'a', using tree set. When there is a query of type x = 0, we can find the 
		//first patient in the range, l - r, using a.ceiling(l), and remove patients until a.ceiling(l) > r. 
		
		//for queries of type x = 1, we use a range minimum segment tree. At position l, insert the value r. 
		
		//when processing queries of type t = 1, we first check whether x, the patient specified in the query, is immune. If they are immune, 
		//then we can print "NO". 
		
		//if they are not immune, find the closest person less and greater than x, which are not immune. Name them L and R. Query the segment
		//tree in the range [L, x], and if the answer is less than R, then print "YES", else, print "N/A"
		
		//the last part works since the queries of type t = 0 are guaranteed to not contradict. Since L is the greatest indexed patient that is
		//less than x, all patients in the interval [L + 1, x - 1] are guaranteed to be immune. This means that any query of x = 1 with l in
		//[L + 1, x - 1] is guaranteed to have r >= x. So in order for x to be the only immune inside the query, we just need to check if r < R. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		TreeSet<Integer> ill = new TreeSet<Integer>();
		for(int i = 0; i < n; i++) {
			ill.add(i);
		}
		int treeSize = (int) Math.pow(2, Integer.toBinaryString(n).length() + 1);
		int[][] tree = new int[Integer.toBinaryString(n).length() + 1][];	//range min tree
		for(int i = 0; i < tree.length; i++) {
			tree[i] = new int[treeSize];
			Arrays.fill(tree[i], Integer.MAX_VALUE);
			treeSize /= 2;
		}
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int t = Integer.parseInt(st.nextToken());
			if(t == 0) {
				int l = Integer.parseInt(st.nextToken()) - 1;
				int r = Integer.parseInt(st.nextToken()) - 1;
				int x = Integer.parseInt(st.nextToken());
				if(x == 0) {
					int next = l;
					while(ill.ceiling(next) != null) {
						next = ill.ceiling(next);
						if(next > r) {
							break;
						}
						ill.remove(next);
					}
				}
				else {
					insert(tree, l, r);
				}
			}
			else {
				int x = Integer.parseInt(st.nextToken()) - 1;
				if(!ill.contains(x)) {
					fout.append("NO\n");
					continue;
				}
				int l = ill.floor(x - 1) == null? 0 : ill.floor(x - 1) + 1;
				int r = ill.ceiling(x + 1) == null? n - 1 : ill.ceiling(x + 1) - 1;
				int min = query(tree, l, x);
				fout.append(min <= r? "YES\n" : "N/A\n");
			}
		}
		System.out.print(fout);
	}
}
