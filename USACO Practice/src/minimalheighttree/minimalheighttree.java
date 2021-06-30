//package minimalheighttree;

import java.util.*;
import java.io.*;

public class minimalheighttree {
	public static void main(String[] args) throws IOException {
		
		//1437D
		
		//since the bfs visits the nodes in order of ascending id, the maximum children one node can have is the maximum ascending subarray following after it. 
		//to make the least depth tree, all we have to do is just greedily add as many nodes as we can to the first layer, and then repeat, going another layer down
		//until we don't have any more nodes.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int counter = 0;
		while(t-- > 0) {
			counter ++;
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int layer = 1;
			int nodesLeft = 1;
			int nextLayer = 0;
			boolean start = true;
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			if(counter == 273) {
//				for(int i : nums) {
//					System.out.print(i + " ");
//				}
//				System.out.println();
			}
			for(int i = 1; i < n; i++) {
				//System.out.println("CUR NODE: " + nums[i]);
				if(start) {
					nextLayer ++;
					nodesLeft --;
					start = false;
				}
				else {
					if(nums[i] < nums[i - 1]) {
						nodesLeft --;
						if(nodesLeft == -1) {
							nodesLeft = nextLayer - 1;
							nextLayer = 1;
							layer ++;
						}
						else {
							nextLayer ++;
						}
					}
					else {
						nextLayer ++;
					}
				}//System.out.println("LAYER: " + layer + " NODES LEFT: " + nodesLeft + " NEXT LAYER: " + nextLayer);
			}
			//System.out.println();
			fout.append(layer).append("\n");
		}
		System.out.print(fout);
	}
}	
