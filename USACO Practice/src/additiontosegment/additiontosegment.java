//package additiontosegment;

import java.util.*;
import java.io.*;

public class additiontosegment {
	
	static ArrayList<ArrayList<Node>> tree;
	
	public static long getValue(int index) {
		int curPriority = -1;
		long ans = 0;
		for(int i = 0; i < tree.size(); i++) {
			//System.out.println(tree.get(i).get(index).priority + " " + tree.get(i).get(index).value);
//			if(tree.get(i).get(index).priority > curPriority) {
//				ans = tree.get(i).get(index).value;
//				curPriority = tree.get(i).get(index).priority;
//			}
			ans += tree.get(i).get(index).value;
			index /= 2;
		}
		return ans;
	}

	
	
	public static void setValueInRange(int low, int high, int value, int priority) {	//low inclusive, high exclusive, adding old value to new value
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
			tree.get(layer).get(index).setValue(value + tree.get(layer).get(index).value, priority);
		}
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
				tree.get(layer).add(new Node(0, -1));
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
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				setValueInRange(low, high, value, priority);
				priority ++;
			}
			else {
				int index = Integer.parseInt(st.nextToken());
				fout.append(getValue(index)).append("\n");
			}
		}
		System.out.print(fout);
	}
}

class Node {
	
	public int priority;
	public long value;
	
	public Node(long value, int priority) {
		this.value = value;
		this.priority = priority;
	}
	
	public void setValue(long value, int priority) {
		this.value = value;
		this.priority = priority;
	}
	
}