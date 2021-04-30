//package assignmenttosegment;

import java.util.*;
import java.io.*;

public class assignmenttosegment {
	
	static ArrayList<ArrayList<Node>> tree;
	
	public static void setRange(int low, int high, int value, int priority) {	//low inclusive, high exclusive
		for(int i = low; i < high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				layer ++;
				increment *= 2;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h >= high) {
					index = temp;
					layer --;
					i += increment / 2;
					break;
				}
			}
			tree.get(layer).set(index, new Node(priority, value));
		}
	}
	
	public static int getValue(int index) {
		int ans = 0;
		int priority = -1;
		for(int i = 0; i < tree.size(); i++) {
			if(tree.get(i).get(index).priority > priority) {
				ans = tree.get(i).get(index).value;
				priority = tree.get(i).get(index).priority;
			}
			index /= 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		tree = new ArrayList<ArrayList<Node>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Node>());
				}
				tree.get(layer).add(new Node(-1, 0));
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		int priority = 0;
		while(m-- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				setRange(low, high, value, priority);
				priority ++;
			}
			else {
				fout.append(getValue(Integer.parseInt(st.nextToken()))).append("\n");
			}
		}
		System.out.print(fout);
	}
}

class Node {
	
	int priority;
	int value;
	
	public Node(int priority, int value) {
		this.priority = priority;
		this.value = value;
	}
	
	public void set(int priority, int value) {
		this.priority = priority;
		this.value = value;
	}
	
}
