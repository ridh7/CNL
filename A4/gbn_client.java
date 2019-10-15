import java.net.*;
import java.io.*;
import java.util.*;

public class gbn_client {

	public static void main(String[] args) {
		try 
		{
			Scanner sc = new Scanner(System.in);
			Socket s = new Socket("localhost", 6666);
			DataOutputStream dos = new DataOutputStream(s.getOutputStream());
			DataInputStream dis = new DataInputStream(s.getInputStream());
			
			int ws = dis.readInt();	
			System.out.println("FRAME SIZE: 10");
			System.out.println("Window size: " + ws);
            int a[] = new int[10];
			int fa, fno;
			for (int i=0; i<a.length; i++)
			{
				if(i%ws == 0 && i>0)
				{
					System.out.print("Enter 1 if all frames have been received: ");
					fa = sc.nextInt();
					dos.writeInt(fa);
					if(fa != 1)
					{
						System.out.print("Enter frame number of corrupted/missing frame: ");
						fno = sc.nextInt();
						dos.writeInt(fno);
						for(int j=fno;j<i;j++)
						{
							a[j]=dis.readInt();
							System.out.println("Received frame is: " + a[j]);
						}
					}
					else
					{
						System.out.println("Acknowledgement sent for frame "+i);
						int ack=dis.readInt();
						if(ack == 1)
							System.out.println("Acknowledgement received");
						else
						{
							System.out.println("Acknowledgement not received");
							for(int j=0;j<i;j++)
							{
								a[j]=dis.readInt();
								System.out.println("Received frame is: " + a[j]);
							}
						}
					}
				}
				a[i] = dis.readInt();
				System.out.println("Received frame is: " + a[i]);
			}
			dis.close();
			dos.close();
			sc.close();
			s.close();			
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
	}
}

