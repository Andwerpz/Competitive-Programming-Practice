//package aromassearch;

import java.util.*;
import java.io.*;

public class aromassearch {
	
	static long x0, y0, ax, ay, bx, by, xs, ys;
	
	public static long dist(long x1, long y1, long x2, long y2) {
		return Math.abs(x1 - x2) + Math.abs(y1 - y2);
	}
	
	public static int getMax(long t, int val) {
		long minDist = 0;
		ArrayList<long[]> nodes = new ArrayList<long[]>();
		nodes.add(new long[] {x0, y0});
		while(nodes.size() < val) {
			long[] prev = nodes.get(nodes.size() - 1);
			long nextX = prev[0] * ax + bx;
			long nextY = prev[1] * ay + by;
			nodes.add(new long[] {nextX, nextY});
		}
		minDist = dist(xs, ys, nodes.get(nodes.size() - 1)[0], nodes.get(nodes.size() - 1)[1]);
		if(minDist < 0) {
			return 0;
		}
		//System.out.println(minDist + " " + t);
		t -= minDist;
		int ans = 0;
		if(t >= 0) {
			ans ++;
		}
		else {
			return 0;
		}
		int pointer = nodes.size() - 2;
		while(pointer >= 0 && t > 0) {
			//System.out.println("YES");
			long[] next = nodes.get(pointer);
			long[] cur = nodes.get(pointer + 1);
			long nextDist = dist(next[0], next[1], cur[0], cur[1]);
			//System.out.println(nextDist);
			t -= nextDist;
			pointer --;
			if(t >= 0) {
				ans ++;
			}
		}
		//System.out.println(minDist);
		t -= dist(x0, y0, nodes.get(nodes.size() - 1)[0], nodes.get(nodes.size() - 1)[1]);
		//System.out.println(dist(x0, y0, nodes.get(nodes.size() - 1)[0], nodes.get(nodes.size() - 1)[1]));
		while(t > 0) {
			long[] prev = nodes.get(nodes.size() - 1);
			long nextX = prev[0] * ax + bx;
			long nextY = prev[1] * ay + by;
			//System.out.println(prev[0] + " " + prev[1]);
			//System.out.println(nextX + " " + nextY);
			long nextDist = dist(nextX, nextY, prev[0], prev[1]);
			//System.out.println(nextDist + " " + t);
			t -= nextDist;
			if(t >= 0) {
				ans ++;
			}	
			nodes.add(new long[] {nextX, nextY});
		}
		
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1292B
		
		//this one was a pain to solve. View tutorial for explanation
		//the nodes are going to be always increasing in distance from each other
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		x0 = Long.parseLong(st.nextToken());
		y0 = Long.parseLong(st.nextToken());
		ax = Long.parseLong(st.nextToken());
		ay = Long.parseLong(st.nextToken());
		bx = Long.parseLong(st.nextToken());
		by = Long.parseLong(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		xs = Long.parseLong(st.nextToken());
		ys = Long.parseLong(st.nextToken());
		long t = Long.parseLong(st.nextToken());
		int ans = 0;
		long px = x0;
		long py = y0;
		int val = 1;
		long prevX = x0;
		long prevY = y0;
		while(true) {
			ans = Math.max(ans, getMax(t, val));
			//System.out.println(px + " " + py + " " + val + " " + ans);
			val ++;
			px *= ax;
			py *= ay;
			px += bx;
			py += by;
			if(px < prevX || py < prevY) {
				break;
			}
			prevX = px;
			prevY = py;
		}
		System.out.println(ans);
	}
}
