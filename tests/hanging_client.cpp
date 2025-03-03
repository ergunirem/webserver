// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>

#include <string>

#define PORT 80

int main(int argc, char const *argv[])
{
   
    int sock = 0;
    struct sockaddr_in serv_addr;
    std::string http_request_mes = "GET / HTTP/1.1\r\n"
                            "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                            "Host: www.tutorialspoint.com\r\n"
                            "Content-Type: application/x-www-form-urlencoded\r\n"
                            "Content-Length: 49\r\n"
                            "Accept-Language: en-us\r\n"
                            "Accept-Encoding: gzip, deflate\r\n"
                            "Connection: Keep-Alive\r\n"
                            "Trailer: Expires\r\n"
                            "Transfer-Encoding: chunked\r\n\r\n"

                            "4\r\n"
                            "Wiki\r\n"
                            "5\r\n"
                            "pedia\r\n"
                            "E\r\n"
                            " in\r\n\r\nchunks.\r\n"
                            "30\r\n"
                            "Expires: Wed, 21 Oct 2015 07:28:00 GMT\r\n"
                            "\r\n";

    std::string bla_mesasage = "bla";
    std::string long_message = "GET V57gxvvkHGfQ+Y7mTnEcSQiSlff80v4+s5b49VpcyUF45J5ZeMrRuERjnjGRBjGwD8282QRoXOmE1308vB6kr6viaf5aK4NeK7MBpm4RZ5RkayYyM1MkzQs/ztPODpEPnMIg1UdwVTi2nfc92c7rdU4ADHU+N4yUNtI3+wmfFlMiPF14d8f6QM3sJSUwllkzmua9JiUAq14dxUt24huefy07USXRMW7D8oZ7tlPO91Yi4QNOaHpf6orWA2mVoMMuTNLvT6Xg7ZIfH/Qal80jhrza3qhNm9IEY9SetIczC9hy0hUaxUpgppzLSPuTf/Yw2OJnilpmobsylZzrzZe6/q5nRcbJonvtN8XhAFNt1bNN9czndbOz/3qmKabO22X0N9fBDjd5Mh+hIaZ4dXaa0vqLpjAV9POpqj3nYBqEKoiWcxRKfqf4BXujWE7OaiVOOxVVygyhNha/gC7muGvVJkz1PPlz/uaWAiNnH25EiKcC2PnktXYdkBdParUhQI/oexObbSDyqdmheCMLDTRpC1wU7ctzfnNpw9KXwxQDdVoEXO7XlLy7649zKRR0ICvqMdTHleiT9oEesSG2AmELwi2lBy46yeKaQIBynvDrZ8wFE1Jajb2DNs8tPdVcITBkqJDNN/gQUPi5s5Khs9PuMz3KdluZ9amPKzZytUriXqUNkKl+ueBVKZR3YT9nxFFCdnNyD7MQoicBCYS05rmE/sBH24X8u6JwYGIZ/dW3Su7GeEhu7LGps+qrR0M6Q/AOAeE21YS/4ztzFXqVC4HaWZIE1uBR6KagPLDIVtvF/NFAex8/IguDXRn5aIwbmpTLFBdyQtWjQGTHae+584FlpB4ye5AAx8wkLu8ZbNtzzGSxCYyEw2E0pNAGILgzHk0LhyN7lFWpM5oVcYx7Dl5nRH4SDYtmgK1WNqCnb8lrbd8aEP5gBu8GdHCd1iOOnaaWMgQV8gZQWr8N5QYNclOfNMUFii3gVCq6EbBAq78eyasRa1kRflwFj3WGa6+BpoDheUBCJi/XjiYcP6EEIJuj3bZkDsbmS5iKUyAMokmd+KuisyO+a78ZVgaQrXTulctM4Od2tk0k2yd4WqHUNm8JWhSwF+64gRV2evMFK79oOCg0YPxDZxoaly2AutKp3lWmwV/CxEG7Qe+wvOAg6Z2AB55zZrGOWKEc/cgMzZZ1RxvfmLiD2ajTDTkCFHf067o6PfrKnpe06jxvdOCFZE16lYiGgCIMpQEaRbzlGeSpJnfaPUhGz4PlClepwm9cGqaDC5Mz3aTJaOXVNE8H2uM3WsuFlm6497/8bZ8SrFA0BxNKwDSnW31WisF9FZZ7YvEx/mmRtNOmIRA4kBnHPId5nzBxTNfe0g2yTMtdEN/KuEVELXaDPf1DHnfkesPGSZuHcacZowpPwT+tlZfp5gNLnY9w9WI3KXygAtqmHuLW/Rvf1hTqF1qPX/AAGRp2oAQBQjhW9JWvlXvWnvTwDxkKY+GqSZgOMe0riGnTmfC7kmLpUDehzuApnpy47Of8q8V3k6dKVULUYFms9ls+l83rnf8yF/ipccU4EzR4w7p8aIqsBILEF3mIESmbdrkM5fjbWQdcr3UK8/ELFU2I6AgHV2iF7bHwW/E6SCP8wQd8z63C5pGWPcnfp7818URlA/g77Lj9XTU2jscq86tKQ4b1uZU3LXFRj4SmbYbS5qNKz5ftcdoAK8RNSBS7TKKQYKMjMmOrMhLjB6hLwGBeGXlovJo6L8X/pG+R4aCuUu+Uu0kyS2ajs2Fg+njJJhP8F4dRnMrTQWx8eRLlWolIUEzIWi4gjl8KRD8wD3tw1h4jESvtNq55+zm9xvSc50ij1EN9p2o2brbpc+L3Q4suiS9CHFLsI2xO7W/7MqFqg580Ea0rJegleIPYCnKUlaevgw6cCtmOJbl4rxLH+ofQwR0G3KebZ1+u66tb4stOfTSgZErQIMArC2h1wEFKY5S4KJz1s49G2AN9DrgGFodGppRKKf8Ufg1l4tYNx4PIIkGSSHJrpJYIaR4DsfzpupHv5/D0TYnnzETK2d1lkCMNs/FXhsZXuCquqOJY5+WKXoalgFP42GIs7zxVIPL1UskSWZ/52L38VAYoEf3zPwUmUe5ZmaAFwzHvvwQaPz1s3DB+GuM+S1een75CaE5iMA3DwYPC7IUI0hZVFsZj1Wqos+Hk5yCNdMs1QVSd9QblOLxQciBmfdp+GymGeoUErvYysDoUreYbPKf7C/z9D/eXGNXyeSXGRHbgE0AKXtIpIHCEc8X19vO1wFDww2dIhDnPmDz+8ByB6uv8TnyXP2BWcimClRjXCxsbBtZgb0wJ4wZx8LmXjjK4jgDM7Sn0AFNWgk+K0IIcgg7eWXRGK/QhWAgCg95GQ/hjJ1FJ0oGU8q77G8IqsoDRiTkoYr9W0gXXp/8VAELexRTyYuVZP/Qblgxd+FnZhEbqj6PDReU8LKzbRHrvP4xXnaOLVgQIzEjm+wIKGwEybes/uPVuSgBDOGrfpzgHZSqedxetmBdgxAQLShbupNKTjWUkJqJ4+TclepaTlLJIGsduB5xQuOjZwpmEns+4CuRsft6NRFjkcr3SzCmIUUSN0j1c3ANP7uN9tBWGJwTUCkTgNkF8TFvo3ZC9vVYrTPApIY5fWQJU/lssDlVOuLA/pom9i3bXlJeAZXt2a+6p8gFWDw HTTP/1.1\r\n";
    std::string longest_message = "GET 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"
                            "HTTP/1.1\r\n";
    char buffer[2048] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    // send(sock , bla_mesasage.c_str() , 1 , 0 );
    // sleep(1);
    // send(sock , bla_mesasage.c_str() + 1 , 1 , 0 );
    // sleep(1);
    // send(sock , bla_mesasage.c_str() + 2 , 1 , 0 );

    // send(sock, bla_mesasage.c_str(), bla_mesasage.size(), 0);

    // std::cout << "size: " << longest_message.size() << std::endl;
    // send(sock, longest_message.c_str(), 1, 0);
    // sleep(1);
    // send(sock, longest_message.c_str() + 1, longest_message.size() - 1, 0);

    send(sock, http_request_mes.c_str(), http_request_mes.size(), 0);
    

    long valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}