#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "base.h"

MenuItem* Method::get_encryption_ptr(){
    MenuItem* encryption_ptr = new MenuItem;
    encryption_ptr->name = "encryption";
    encryption_ptr->submenu = {
        {"encryption +", {
            {"md5sum +", {{"show manual#man md5sum#"}}},
            {"sha512sum +", {{"show manual#man sha512sum#"}}},
            {"openssl +", {{"file/tardir encryption with aes-256-cbc (passwd promption needed)#openssl enc -aes-256-cbc -in ${unencrypted_file} -out ${encrypted_file}#"},
                           {"file/tardir decryption with aes-256-cbc (passwd promption needed)#openssl enc -d -aes-256-cbc -in ${encrypted_file} -out ${unencrypted_file}#"}}}},
        },
    };
    return encryption_ptr;
}

#endif
