//package notescaping;

import java.util.*;
import java.io.*;

public class notescaping {
	public static void main(String[] args) throws IOException {
		
		//1627E
		
		//hoo boy.. this one took a while
		//need to work on implementation
		
		//Since the cost values are completely arbitrary, the only way to solve this is to simulate the situation.
		
		//If you were to simulate it completely, notice that you would have to calculate the minimums cost to get to 
		//every room in one floor, before moving onto the next floor. 
		
		//instead of calculating the costs to every room in a floor, you only need to calculate the cost to every room with a ladder
		//entrance inside. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] floorCost = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				floorCost[i] = Integer.parseInt(st.nextToken());
			}
			ArrayList<ArrayList<long[]>> ladders = new ArrayList<ArrayList<long[]>>();
			for(int i = 0; i < n; i++) {
				ladders.add(new ArrayList<long[]>());
			}
			for(int i = 0; i < k; i++) {
				st = new StringTokenizer(fin.readLine());
				long[] next = new long[6];
				for(int j = 0; j < 5; j++) {
					next[j] = Integer.parseInt(st.nextToken());
					if(j < 4) {
						next[j] --;
					}
				}
				ladders.get((int) next[0]).add(next);
			}
			ArrayList<ArrayList<long[]>> exits = new ArrayList<ArrayList<long[]>>();	//cost, room
			for(int i = 0; i < n; i++) {
				exits.add(new ArrayList<long[]>());
			}
			for(long[] l : ladders.get(0)) {
				long nextVal = l[1] * floorCost[0] - l[4];
				long c = l[2];
				long d = l[3];
				exits.get((int) c).add(new long[] {nextVal, d});
			}
			//go through the floors
			for(int i = 1; i < n - 1; i++) {
				//check if it contains an exit
				if(exits.get(i).size() == 0) {
					continue;
				}
				exits.get(i).addAll(ladders.get(i));
				exits.get(i).sort((a, b) -> a[1] == b[1]? Integer.compare(a.length, b.length) : Long.compare(a[1], b[1]));

				
				int minFound = 0;
				
				//left right pass
				long val = 0;
				boolean found = false;
				long prevRoom = 0;
				for(int j = 0; j < exits.get(i).size(); j++) {
					if(exits.get(i).get(j).length == 2) {
						if(!found) {
							minFound = (int) exits.get(i).get(j)[1];
							val = exits.get(i).get(j)[0];
						}
						else {
							long curRoom = exits.get(i).get(j)[1];
							val += Math.abs(prevRoom - curRoom) * floorCost[i];
						}
						found = true;
						val = Math.min(val, exits.get(i).get(j)[0]);
					}
					else {
						if(!found) {
							continue;
						}
						long curRoom = exits.get(i).get(j)[1];
						val += Math.abs(prevRoom - curRoom) * floorCost[i];
						exits.get(i).get(j)[5] = val;
					}
					prevRoom = exits.get(i).get(j)[1];
				}
				
				exits.get(i).sort((a, b) -> a[1] == b[1]? -Integer.compare(a.length, b.length) : Long.compare(a[1], b[1]));
				//right left pass
				val = 0;
				found = false;
				prevRoom = 0;
				for(int j = exits.get(i).size() - 1; j >= 0; j--) {
					if(exits.get(i).get(j).length == 2) {
						if(!found) {
							val = exits.get(i).get(j)[0];
						}
						else {
							long curRoom = exits.get(i).get(j)[1];
							val += Math.abs(prevRoom - curRoom) * floorCost[i];
						}
						found = true;
						val = Math.min(val, exits.get(i).get(j)[0]);
					}
					else {
						if(!found) {
							continue;
						}
						long curRoom = exits.get(i).get(j)[1];
						val += Math.abs(prevRoom - curRoom) * floorCost[i];
						exits.get(i).get(j)[5] = curRoom <= minFound? val : Math.min(val, exits.get(i).get(j)[5]);
					}
					prevRoom = exits.get(i).get(j)[1];
				}

				
				for(long[] e : exits.get(i)) {
					if(e.length == 2) {
						continue;
					}
					long nextFloor = e[2];
					exits.get((int) nextFloor).add(new long[] {e[5] - e[4], e[3]});
				}
			}
			
			
			long ans = Long.MAX_VALUE;
			if(exits.get(n - 1).size() == 0) {
				fout.append("NO ESCAPE\n");
				continue;
			}
			for(long[] e : exits.get(n - 1)) {
				long diff = Math.abs(e[1] - (m - 1));
				ans = Math.min(ans, diff * floorCost[n - 1] + e[0]);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
