import java.io.*;
import java.net.*;
import java.util.*;
public class sr_server {
	
	public static void main(String[] args) {
		try
		{
			int a[] = new int[10];
			Scanner sc=new Scanner(System.in);
	        ServerSocket ss = new ServerSocket(6666);
			Socket s = ss.accept();
			DataInputStream dis = new DataInputStream(s.getInputStream());
			DataOutputStream dos = new DataOutputStream(s.getOutputStream());
			
			System.out.println("FRAME SIZE: 10");
			System.out.println("Enter the frames: ");
	        for(int i=0;i<a.length;i++)
	        {
		        System.out.print("Frame number "+(i+1)+ ": ");
		        a[i]=sc.nextInt();
	        }      
			int ws,ack,fno,fa;
	        System.out.print("Enter window size: ");
		    ws = sc.nextInt();
			dos.writeInt(ws);
			for (int i=0;i<a.length;i++) {
				 if(i%ws == 0 && i>0)
	             {
					 fa=dis.readInt();
					 if(fa != 1)
					 {
						 fno = dis.readInt();
						 System.out.println("Retransmitting the frames");
						 dos.writeInt(a[fno-1]);
					 }
					 else
					 {	
						 System.out.println("Enter 1 if the acknowledgement is received: ");
						 ack = sc.nextInt();
						 dos.writeInt(ack);
						 if(ack == 1)
							 System.out.println("Request for the frame "+i+" received successfully");
						 else
						 {
							 for(int j=0;j<i;j++)
								 dos.writeInt(a[j]);
						 }
					 }
	             }
				 dos.writeInt(a[i]);
				}
			dis.close();
			dos.close();
			s.close();
			ss.close();
			sc.close();
		} 
		catch (IOException e)
		{
			System.out.println(e);
		} 
	}
}