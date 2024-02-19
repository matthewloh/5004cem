import ipaddress

subnet = ipaddress.IPv4Network('192.168.1.0/24')  # Define your subnet here
used_addresses = ['192.168.1.1', '192.168.1.2',
                  '192.168.1.3']  # List of used IP addresses

available_addresses = [str(ip) for ip in subnet.hosts()
                       if str(ip) not in used_addresses]
print("Available IP addresses:", available_addresses)
