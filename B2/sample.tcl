# Create a simulator object 
set ns [new Simulator] 

# Define different colors 
# for data flows (for NAM) 
$ns color 1 Green
$ns color 2 Pink 

# Open the NAM trace file 
set nf [open out.nam w]
set tr [open trace1.tr w]
$ns namtrace-all $nf
$ns trace-all $tr 

# Define a 'finish' procedure 
proc finish {} { 
	global ns nf tr
	$ns flush-trace 
	
	# Close the NAM trace file 
	close $nf 
	close $tr
	
	# Execute NAM on the trace file 
	exec nam out.nam & 
	exit 0
} 

# Create four nodes 
set n0 [$ns node] 
set n1 [$ns node] 
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]  

# Create links between the nodes 
$ns duplex-link $n0 $n1 5Mb 10ms DropTail 
$ns duplex-link $n1 $n2 0.5Mb 20ms DropTail
$ns duplex-link $n3 $n1 5Mb 10ms DropTail
$ns duplex-link $n1 $n4 0.5Mb 20ms DropTail

# Give node position (for NAM) 
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n1 $n3 orient up
$ns duplex-link-op $n1 $n4 orient down 

$ns queue-limit $n1 $n2 10
$ns queue-limit $n1 $n4 5

# Setup a TCP connection 
set tcp [new Agent/TCP] 
$ns attach-agent $n0 $tcp 

set sink [new Agent/TCPSink] 
$ns attach-agent $n2 $sink 
$ns connect $tcp $sink 
$tcp set fid_ 2

# Setup a FTP over TCP connection 
set ftp [new Application/FTP] 
$ftp attach-agent $tcp 
$ftp set type_ FTP 

# Setup a TCP connection 
set tcp1 [new Agent/TCP] 
$ns attach-agent $n3 $tcp1 

set sink1 [new Agent/TCPSink] 
$ns attach-agent $n4 $sink1 
$ns connect $tcp1 $sink1 
$tcp1 set fid_ 1

# Setup a FTP over TCP connection 
set ftp1 [new Application/FTP] 
$ftp1 attach-agent $tcp1 
$ftp1 set type_ FTP

# Schedule events for the CBR and FTP agents 
$ns at 0 "$ftp start"
$ns at 0.5 "$ftp1 start"
$ns at 3.5 "$ftp1 stop"
$ns at 4.0 "$ftp stop"

# Detach tcp and sink agents 
# (not really necessary) 
$ns at 4.5 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n2 $sink"

# Call the finish procedure after 
# 5 seconds of simulation time 
$ns at 5.0 "finish"

# Run the simulation 
$ns run 

