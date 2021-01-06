#include "generator.h"

std::string Generator::randName()
{
	std::string first[3] = { "The-","","" };
	std::string second[163] = { "","Antarctican","Flying","Electric","Fractured","Broken","Clear","Muddy","Yellow","Naked","Invisible","","Hollow","Crass","Light","Dark","Chocolate","Riff","","Mind","Heartless","Rock","Gods of","Sacrifice to","Master","Sleazy","Sisters of","Brothers of","Angry","Dying","Bloody","","Crazy","Shocking","Quiet","Sick","Cynical","Complete","Rude","Spicy","Hurt","Aquatic","Demonic","Obselete","Grieving","Deep","Ancient","Dead","Impossible","Violent","Juvenile","Real","Long","Meek","Orange","Grey","Moaning","","Jobless""Awful","Typical","Acid","Little","Obscene","Dry","Sticky","Rapid","Addictive","Cool","Tame","Royal","","Cruel","Loud","High","Big","Chemical","Mighty","Wretched","Drunk","General","Daily","Fluffy","Elfin","Two","Three","Scandalous","","Four","Five","Only","Sex","Rustic","Empty","Ugly","Evil","Disturbed","Unnatural","Ghostly","Heavy","","Modern","Fresh","Ragged","","Innocent","Acoustic","Rich","Lewd","Perverted","Infernal","Abusive","","Quick","Blue-eyed","Stormy","Icy","True","Chilly","Jaded","Black","Creepy","Screaming","Stabbing","Tilted","Spurned","Unreal","","Pissed","Awesome","Spinal","Dirty","Black","Scarlet","Gang of","Major","Headless","Tortured","Hybrid","Sonic","Riot","Hell","Damned","Pink","White","Green","Insidious","Spiritual","Broken","Abusive","Dark","Real","Enchanted","Imaginary","Daily","Lame","Future","Automatic","Shrill","Scarce","","Noctural","Asian","Streetlight" };
	std::string third[137] = { "Gods","Devil","Letter","Men","Ladies","Widow","Statement","Scarecrow","Chickens","Animal","Mice","Cheese","Punishment","Thrill","Pain","Death","Truth","Temper","Summer","Anarchy","Antichrist","Self","Face","Tears","Story","Blows","Invention","Inc.","Window","Thrones","Surgery","Metal","Meeks","Ancestors","Stoners","Spiders","Brothers","Sisters","Of Fate","Tramps","Behaviour","Road","Tree","Beetles","Sunday","Zone","Boys","Girls","Flag","Dragon","Kiss","Youth","Space","Island","Cream","Punk","Tones","Enemy","Fighters","Birds","Pistols","Mind","Bait","Worms","Fly","Persuasion","Roof","Discovery","Children","School","Theory","Coders","Zebras","Noobs","Crowd","Tail","Nest","Library","Ship","Magic","Question","Error","Rhythm","Babies","Cobwebs","Turn","Aliens","Division","Things","Attraction","Ministers","Ritual","Guns","Night","Winter","Company","Picture","Impulse","Force","Moments","Caress","Skyline","Friday","Abuse","Afternoon","Morning","Evening","Nobodies","Remains","Waters","Party","Martians","Fire","Harvest","Star","911","Route","War","Sky","Roses","Threat","Desert","Head","Brigade","Victim","Generator","Zombies","Church","Dream","Nightmare","Heads","Jam","Horsemen","Symptoms","Emissions","Vengeance","Frustration" };

	return first[rand() % 3] + second[rand() % 163] + "-" + third[rand() % 137];
}

void Generator::generateUsers(std::vector<User>& users, int n)
{
	Hash hashRand;
	User user;

	int balance;
	std::string Name;

	srand(time(0));
	for (int i = 0; i < n; i++) {

		Name = randName();
		user.setName(Name);

		balance = (rand() % 1000000) + 100;
		user.setBalance(balance);

		user.setPublic_key(hashRand.toHash(std::to_string(balance) + Name));

		users.push_back(user);
	}
}

void Generator::generateTransactions(std::vector<Transaction>& transactions, std::vector<User>& users, int n)
{
	Hash hashRand;
	Transaction transaction;

	std::string Transaction_id;
	std::string Sender_key;
	std::string Receiver_key;
	int Sum;

	for (int i = 0; i < n; i++) {




		//transaction.setTransaction_id(hashRand.toHash((Transaction_id + Sender_key + Receiver_key) + std::to_string(Sum)));
		transactions.push_back(transaction);
	}
}
