//package boringsegments;

import java.util.*;
import java.io.*;

public class boringsegments {
	
	static ArrayList<ArrayList<Node>> tree;
	
	public static void addToSegment(int l, int r, int val) {
		r += 1;
		int index = l;
		int increment = 1;
		int layer = 0;
		for(int i = l; i <= r; i += 0) {
			while((index / 2) * increment * 2 >= l && (index / 2) * increment * 2 + increment * 2 <= r) {
				index /= 2;
				increment *= 2;
				layer ++;
			}
			while(index * increment < l || index * increment + increment > r) {
				if(increment == 1) {
					return;
				}
				if(index * increment < l) {
					index *= 2;
					index += 1;
				}
				else {
					index *= 2;
				}
				increment /= 2;
				layer --;
			}
			if(index > r) {
				return;
			}
			i += increment;
			int temp = index;
			tree.get(layer).get(index).add += val;
			tree.get(layer).get(index).min += val;
			for(int j = layer + 1; j < tree.size(); j++) {
				int cur = tree.get(j - 1).get(index).min;
				int other = tree.get(j - 1).get(index % 2 == 1? index - 1 : index + 1).min;
				index /= 2;
				tree.get(j).get(index).min = Math.min(cur, other) + tree.get(j).get(index).add;
			}
			index = temp;
			index ++;
		}
	}
	
	public static int getMinimumInRange(int l, int r) {
		int ans = Integer.MAX_VALUE;
		r ++;
		int index = l;
		int increment = 1;
		int layer = 0;
		for(int i = l; i <= r; i += 0) {
			
			while((index / 2) * increment * 2 >= l && (index / 2) * increment * 2 + increment * 2 <= r) {
				index /= 2;
				increment *= 2;
				layer ++;
			}
			while(index * increment < l || index * increment + increment > r) {
				if(increment == 1) {
					return ans;
				}
				if(index * increment < l) {
					index *= 2;
					index += 1;
				}
				else {
					index *= 2;
				}
				increment /= 2;
				layer --;
			}
			if(index > r) {
				return ans;
			}
//			while(true) {
//				int temp = index;
//				index /= 2;
//				increment *= 2;
//				layer ++;
//				int low = index * increment;
//				int high = low + increment;
//				if(low < l || high > r) {
//					index = temp;
//					increment /= 2;
//					layer --;
//					break;
//				}
//			}
			i += increment;
			int temp = index;
			int curAns = tree.get(layer).get(index).min;
			//System.out.println("---" + layer + " " + index);
			for(int j = layer + 1; j < tree.size(); j++) {
				index /= 2;
				curAns += tree.get(j).get(index).add;
				//System.out.println(tree.get(j).get(index) + " " + j + " " + index);
				//System.out.println(tree);
			}
			//System.out.println(curAns);
			ans = Math.min(ans, curAns);
			if(ans == 0) {
				return 0;
			}
			index = temp;
			index ++;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1555E
		
		//java is probably too slow for this one without serious optimizations. 
		
		//use segment tree to update on range. To check if valid, just run a range minimum query over 0 - (m - 1).
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken()) * 2;
		int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(m) / Math.log(2))));
		tree = new ArrayList<ArrayList<Node>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Node>());
				}
				tree.get(layer).add(new Node(0, 0));
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		int[][] segments = new int[n][3];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int l = (Integer.parseInt(st.nextToken()) - 1);
			int r = (Integer.parseInt(st.nextToken()) - 1);
			l += l;
			r += r;
			//System.out.println(l + " " + r);
			int w = Integer.parseInt(st.nextToken());
			segments[i][0] = l;
			segments[i][1] = r;
			segments[i][2] = w;
		}
		//System.out.println(m);
		Arrays.sort(segments, (a, b) -> a[2] - b[2]);
		int pointer = 0;
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			while(pointer < n && getMinimumInRange(0, m - 2) == 0) {
				addToSegment(segments[pointer][0], segments[pointer][1], 1);
				//System.out.println(segments[pointer][0] + " " + segments[pointer][1]);
				pointer ++;
			}
			//System.out.println(tree);
			if(getMinimumInRange(0, m - 2) != 0) {
				//System.out.println("-----ANS---- " + i + " " + pointer);
				ans = Math.min(ans, segments[pointer - 1][2] - segments[i][2]);
			}
			else if(pointer == n) {
				break;
			}
			addToSegment(segments[i][0], segments[i][1], -1);
		}
		System.out.println(ans);
	}
}

class Node {
	
	public int add, min;
	
	public Node(int add, int min) {
		this.add = add;
		this.min = min;
	}
	
	public String toString() {
		return this.add + this.min + "";
	}
	
}
