import java.io.IOException;
import java.util.*;

public class main {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Scanner sc = new Scanner(System.in);
		char e = 0;
		
		do
		{
			int[] mask = new int[4];
			int hosts = 0;
			int sb = 0;
			int flag = 0;
			System.out.print("Enter IP: ");
			String ip = sc.next();
			String[] ip_n = ip.split("\\.");
			if(ip_n.length != 4)
			{
				System.out.println("Invalid IP!");
			}
			else
			{
				int[] ipi = new int[4];
				for(int i = 0; i < 4; i++)
				{
					ipi[i] = Integer.parseInt(ip_n[i]);
					if(ipi[i] > 255 || ipi[i] < 0)
					{
						System.out.println("Error in " + "octet " + (i+1));
						System.out.println(ipi[i] + " does not lie between 0 and 255");
						System.exit(0);
					}
				}
				char c = 0;
				if(ipi[0] < 127)
				{
					c = 'a';
					System.out.println("IP belongs to class A");
					System.out.println("Default Subnet Mask: 255.0.0.0");
				}
				else if(ipi[0] < 191)
				{
					c = 'b';
					System.out.println("IP belongs to class B");
					System.out.println("Default Subnet Mask: 255.255.0.0");
				}
				else if(ipi[0] < 224)
				{
					c = 'c';
					System.out.println("IP belongs to class C");
					System.out.println("Default Subnet Mask: 255.255.255.0");
				}
				else if(ipi[0] < 240)
				{
					System.out.println("IP belongs to class D");
					System.out.println("Subnetting not defined");
				}
				else
				{
					System.out.println("IP belongs to class E");
					System.out.println("Subnetting not defined");
				}
				do
				{
					System.out.print("Enter the number of subnets that you want to create: ");
					sb = sc.nextInt();
					if(c == 'c')
					{
						if(sb < 2 || sb > 256)
						{
							System.out.println("Number of subnets should lie between 2 and 256");
							flag = 1;
						}
						else
						{
							mask[0] = mask[1] = mask[2] = 255;
							flag = 0;
							hosts = 256;
						}
					}
					else if(c == 'b')
					{
						if(sb < 2 || sb > 65536)
						{
							System.out.println("Number of subnets should lie between 2 and 65536");
							flag = 1;
						}
						else
						{
							mask[0] = mask[1] = 255;
							flag = 0;
							hosts = 65536;
						}
					}
					else if(c == 'a')
					{
						if(sb < 2 || sb > 16777216)
						{
							System.out.println("Number of subnets should lie between 2 and 16777216");
							flag = 1;
						}
						else
						{
							mask[0] = 255;
							flag = 0;
							hosts = 16777216;
						}
					}
				}
				while(flag != 0);
				int mask1 = 0;
				for(mask1 = 0; mask1 < 24; mask1++)
				{
					if(sb <= Math.pow(2, mask1))
						break;
				}
				if(c == 'c')
				{
					for(int i = 7; mask1 > 0; i--, mask1--)
					{
						mask[3] += Math.pow(2, i);
					}
				}
				else if(c == 'b')
				{
					if(mask1 >= 8)
					{
						mask[2] = 255;
						mask1 -= 8;
						for(int i = 7; mask1 > 0; i--, mask1--)
						{
							mask[3] += Math.pow(2, i);
						}
					}
					else
					{
						for(int i = 7; mask1 > 0; i--, mask1--)
						{
							mask[2] += Math.pow(2, i);
						}
					}
				}
				else if(c == 'a')
				{
					if(mask1 >= 16)
					{
						mask[1] = 255;
						mask[2] = 255;
						mask1 -= 16;
						for(int i = 7; mask1 > 0; i--, mask1--)
						{
							mask[3] += Math.pow(2, i);
						}
					}
					else if(mask1 >= 8)
					{
						mask[1] = 255;
						mask1 -= 8;
						for(int i = 7; mask1 > 0; i--, mask1--)
						{
							mask[2] += Math.pow(2, i);
						}
					}
					else
					{
						for(int i = 7; mask1 > 0; i--, mask1--)
						{
							mask[1] += Math.pow(2, i);
						}
					}
				}
				String subnet = mask[0] + "." + mask[1] + "." + mask[2] + "." + mask[3];
				System.out.println("New subnet mask: " + subnet);
				System.out.println("Enter interface for assigning IP: ");
				String ifc = sc.next();
				try {
					Process pr = Runtime.getRuntime().exec("sudo ifconfig " + ifc + " " + ip + " netmask " + subnet);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				System.out.println("IP assigned successfully");
				int f = 0;
				String ping;
				do
				{
					System.out.println("Enter IP address to ping: ");
					ping = sc.next();
					String[] ip_x = ping.split("\\.");
					if(ip_x.length != 4)
					{
						f = 1;
						System.out.println("Invalid IP!");
					}
					else
					{
						f = 0;
						int[] ipx = new int[4];
						for(int i = 0; i < 4; i++)
						{
							ipx[i] = Integer.parseInt(ip_x[i]);
							if(ipx[i] > 255 || ipx[i] < 0)
							{
								System.out.println("Error in " + "octet " + (i+1));
								System.out.println(ipi[i] + " does not lie between 0 and 255");
								f = 1;
							}
						}
					}
				}
				while(f == 1);
				try
				{
					Process p = Runtime.getRuntime().exec("ping -c 5 " + ping);
					int ret = p.waitFor();
					if(ret == 0)
						System.out.println("Pinged successfully");
					else if(ret == 2)
						System.out.println("Host unreachable");
					else if(ret == 256)
						System.out.println("Host shutdown");
				}
				catch(Exception ev)
				{
					ev.printStackTrace();
				}
				System.out.print("Continue? (Y/N) ");
				e = sc.next().charAt(0);
			}
		}
		while(e == 'Y' || e == 'y');
		sc.close();
	}

}
