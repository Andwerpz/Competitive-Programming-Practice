//package segmentwiththemaximumsum;

import java.util.*;
import java.io.*;

public class segmentwiththemaximumsum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) (Math.pow(2, (Math.ceil(Math.log10(n) / Math.log10(2)))));
		ArrayList<ArrayList<Node>> tree = new ArrayList<ArrayList<Node>>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < treeSize; i++) {
			int next = Integer.MIN_VALUE;
			if(i < n) {
				next = Integer.parseInt(st.nextToken());
			}
			int layer = 0;
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Node>());
				}
				if(layer == 0) {
					tree.get(layer).add(new Node(next, next, next));
				}
				else {
					Node node = new Node(0, 0, 0);
					int size = tree.get(layer - 1).size();
					node.recalculate(tree.get(layer - 1).get(size - 2), tree.get(layer - 1).get(size - 1));
					tree.get(layer).add(node);
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		long max = tree.get(tree.size() - 1).get(0).maxSegment;
		if(max < 0) {
			fout.append("0\n");
		}
		else {
			fout.append(tree.get(tree.size() - 1).get(0).maxSegment + "\n");
		}
		while(m-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int i = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			tree.get(0).set(i, new Node(v, v, v));
			i /= 2;
			for(int l = 1; l < tree.size(); l++) {
				//System.out.println(l + " " + i);
				Node a = tree.get(l - 1).get(i * 2);
				Node b = tree.get(l - 1).get(i * 2 + 1);
				tree.get(l).get(i).recalculate(a, b);
				i /= 2;
			}
			long maxSegment = tree.get(tree.size() - 1).get(0).maxSegment;
			if(maxSegment < 0) {
				fout.append("0\n");
			}
			else {
				fout.append(tree.get(tree.size() - 1).get(0).maxSegment).append("\n");
			}
		}
		System.out.print(fout);
	}
}

class Node {
	
	public long prefix;
	public long suffix;
	public long sum;
	public long maxSegment;
	
	public Node(long pfx, long sfx, long sum) {
		this.prefix = pfx;
		this.suffix = sfx;
		this.sum = sum;
		this.maxSegment = sum;
	}
	
	public void recalculate(Node a, Node b) {	//node a is before node b, in other words, a is to the left of node b
		this.maxSegment = Math.max(a.maxSegment, Math.max(b.maxSegment, a.suffix + b.prefix));
		this.prefix = Math.max(a.prefix, a.sum + b.prefix);
		this.suffix = Math.max(b.suffix, b.sum + a.suffix);
		this.sum = a.sum + b.sum;
	}
}
