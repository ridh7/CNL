BEGIN {
	pktdrop = 0;
	total = 0;
}
{
	event = $1;
	if(event == "d")
	{
		pktdrop++;
	}
	total++;
}
END {
	printf("Total packets dropped: %d\n", pktdrop);
	printf("Throughtput: %f\n", (total - pktdrop) / total);
}
