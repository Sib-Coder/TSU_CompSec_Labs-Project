#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <linux/inet.h>
#include <net/sock.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sib-Coder");
MODULE_DESCRIPTION("Kernel module for opening a socket for listening");
MODULE_VERSION("0.01");

static struct socket *sock;

static int __init lkm_example_init(void)
{
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr = {
            .s_addr = htonl(INADDR_ANY)
        }
    };

    int err;

    err = sock_create(AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
    if (err < 0) {
        printk(KERN_ERR "Failed to create socket\n");
        return err;
    }

    err = sock->ops->bind(sock, (struct sockaddr *)&saddr, sizeof(saddr));
    if (err < 0) {
        printk(KERN_ERR "Failed to bind socket\n");
        sock_release(sock);
        return err;
    }

    err = sock->ops->listen(sock, 5);
    if (err < 0) {
        printk(KERN_ERR "Failed to listen on socket\n");
        sock_release(sock);
        return err;
    }

    printk(KERN_INFO "Socket listening on port 8080\n");

    return 0;
}

static void __exit lkm_example_exit(void)
{
    if (sock) {
        sock_release(sock);
    }
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);

