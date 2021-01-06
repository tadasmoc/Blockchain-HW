#include "blockchain.h"

// Block

long long int Block::timestampFunct()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Block::Block()
{
	merkel_hash = "";
	prev_hash = "";
	timestamp = timestampFunct();
	version = 0;
	nonce = 0;
	difficulty = 0;
}

Block::Block(std::string Merkel_hash, std::string Prev_hash, int Version, long int Nonce, int Difficulty)
{
	merkel_hash = Merkel_hash;
	prev_hash = Prev_hash;
	timestamp = timestampFunct();
	version = Version;
	nonce = Nonce;
	difficulty = Difficulty;
}

Block::~Block(){}

// Transaction

Transaction::Transaction()
{
	transaction_id = "";
	sender_key = "";
	receiver_key = "";
	sum = 0;
}

Transaction::Transaction(std::string Transaction_id, std::string Sender_key, std::string Receiver_key, int Sum)
{
	transaction_id = Transaction_id;
	sender_key = Sender_key;
	receiver_key = Receiver_key;
	sum = Sum;
}

Transaction::~Transaction(){}

// Generator

std::string Generator::randName()
{	
	std::string first[3] = { "The-","","" };
	std::string second[163] = { "","Antarctican","Flying","Electric","Fractured","Broken","Clear","Muddy","Yellow","Naked","Invisible","","Hollow","Crass","Light","Dark","Chocolate","Riff","","Mind","Heartless","Rock","Gods of","Sacrifice to","Master","Sleazy","Sisters of","Brothers of","Angry","Dying","Bloody","","Crazy","Shocking","Quiet","Sick","Cynical","Complete","Rude","Spicy","Hurt","Aquatic","Demonic","Obselete","Grieving","Deep","Ancient","Dead","Impossible","Violent","Juvenile","Real","Long","Meek","Orange","Grey","Moaning","","Jobless""Awful","Typical","Acid","Little","Obscene","Dry","Sticky","Rapid","Addictive","Cool","Tame","Royal","","Cruel","Loud","High","Big","Chemical","Mighty","Wretched","Drunk","General","Daily","Fluffy","Elfin","Two","Three","Scandalous","","Four","Five","Only","Sex","Rustic","Empty","Ugly","Evil","Disturbed","Unnatural","Ghostly","Heavy","","Modern","Fresh","Ragged","","Innocent","Acoustic","Rich","Lewd","Perverted","Infernal","Abusive","","Quick","Blue-eyed","Stormy","Icy","True","Chilly","Jaded","Black","Creepy","Screaming","Stabbing","Tilted","Spurned","Unreal","","Pissed","Awesome","Spinal","Dirty","Black","Scarlet","Gang of","Major","Headless","Tortured","Hybrid","Sonic","Riot","Hell","Damned","Pink","White","Green","Insidious","Spiritual","Broken","Abusive","Dark","Real","Enchanted","Imaginary","Daily","Lame","Future","Automatic","Shrill","Scarce","","Noctural","Asian","Streetlight" };
	std::string third[137] = { "Gods","Devil","Letter","Men","Ladies","Widow","Statement","Scarecrow","Chickens","Animal","Mice","Cheese","Punishment","Thrill","Pain","Death","Truth","Temper","Summer","Anarchy","Antichrist","Self","Face","Tears","Story","Blows","Invention","Inc.","Window","Thrones","Surgery","Metal","Meeks","Ancestors","Stoners","Spiders","Brothers","Sisters","Of Fate","Tramps","Behaviour","Road","Tree","Beetles","Sunday","Zone","Boys","Girls","Flag","Dragon","Kiss","Youth","Space","Island","Cream","Punk","Tones","Enemy","Fighters","Birds","Pistols","Mind","Bait","Worms","Fly","Persuasion","Roof","Discovery","Children","School","Theory","Coders","Zebras","Noobs","Crowd","Tail","Nest","Library","Ship","Magic","Question","Error","Rhythm","Babies","Cobwebs","Turn","Aliens","Division","Things","Attraction","Ministers","Ritual","Guns","Night","Winter","Company","Picture","Impulse","Force","Moments","Caress","Skyline","Friday","Abuse","Afternoon","Morning","Evening","Nobodies","Remains","Waters","Party","Martians","Fire","Harvest","Star","911","Route","War","Sky","Roses","Threat","Desert","Head","Brigade","Victim","Generator","Zombies","Church","Dream","Nightmare","Heads","Jam","Horsemen","Symptoms","Emissions","Vengeance","Frustration" };

	return first[rand() % 3] + second[rand() % 163] + "-" + third[rand() % 137];
}

void Generator::generateUsers(std::vector<User>& users, int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++) {
		User user;
		user.setName(randName());
		user.setPublic_key(std::to_string(i));
		user.setBalance(i * n);

		users.push_back(user);
	}
}