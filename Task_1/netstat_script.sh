#!/bin/bash

# Display Network connections
echo "Network connections (TCP & UDP):"
echo -e "Only showing 20 of the entries..."
netstat -t | head -n 10
netstat -u | head -n 10
# Display Routing tables
echo -e "\nRouting tables:"
netstat -r

# Display Interface statistics
echo -e "\nInterface statistics:"
netstat -i

# Display Masquerade connections
echo -e "\nMasquerade connections:"
netstat -M

# Display Multicast memberships
echo -e "\nMulticast memberships:"
netstat -g
