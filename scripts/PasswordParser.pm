package PasswordParser;

use strict;
use YAML;

my $keychain_id = 'eng@opensourcery.com';

{
	sub parseEncrypted {
		my $pass_gpg = shift @_;
		my $eng_pass;
		my $remember = 0;
		
		if (`uname` eq "Darwin\n") {
			
			print "attempting to use Keychain....\n";
			
			$eng_pass = `security 2>&1 >/dev/null find-generic-password -ga eng\@opensourcery.com`;
			($eng_pass) = $eng_pass =~ /"(.*)"/;
			
			if (! defined $eng_pass) {
				$remember = "true";
				print "hmmm, couldn't find the passphrase in your keychain.\n";
			}
			
		}
		if (! defined $eng_pass) {
			print 'enter engineering passphrase: ';
			$eng_pass = <STDIN>;
			chomp $eng_pass;
		}
		
		my $passfile = `echo $eng_pass | gpg --quiet --passphrase-fd 0 -d $pass_gpg`;
		die ("decryption failed") if $?;
		
		remember_pass($eng_pass) if $remember;
		
		return YAML::Load($passfile);
	}


	sub remember_pass {
		
		my $passphrase = shift @_;
		
		`security add-generic-password -a '$keychain_id' -s 'OpenSourcery Engineering Passphrase' -p '$passphrase'`
	
	}


}

1;
