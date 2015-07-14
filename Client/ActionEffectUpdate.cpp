#include "SystemPrerequisites.h"
#include "ActionEffectUpdate.h"
#include "ISceneNode2D.h"
#include "ActorEffect.h"

namespace Ogre
{
	typedef std::map< Real, Real >		MapTimeReal;
	typedef std::map< Real, Vector2 >	MapTimeVector2;
	typedef std::map< Real, Vector3 >	MapTimeVector3;


	struct AffectFrame
	{
		AffectFrame()
			: timePos( 0.f )
		{

		}

		Real	timePos;
	};
	
	typedef std::map< Real, AffectFrame* >	MapKeyFrame;

	void	find2NeighbouringKeyframe( const MapKeyFrame& frames, Real timePos, AffectFrame*& left, AffectFrame*& right, Real& factor )
	{
		left = 0;
		right = 0;

		MapKeyFrame::const_iterator iter = frames.begin();
		MapKeyFrame::const_iterator iterEnd = frames.end();
		
		while ( iter != iterEnd )
		{
			AffectFrame* current = iter->second;

			if ( current->timePos <= timePos )
			{
				left = current;
			}

			if ( current->timePos >= timePos && right == 0 )
			{
				right = current;
			}

			++iter;
		}

		float leftDistance = 0;
		float rightDistance = 0;

		if ( left )
		{
			leftDistance = timePos - left->timePos;
		}
		else
		{
			left = frames.begin()->second;

			leftDistance = 0;
		}

		if ( right )
		{
			rightDistance = right->timePos - timePos;
		}
		else
		{
			right = frames.rbegin()->second;
			rightDistance = 0;
		}

		if ( leftDistance + rightDistance == 0 )
		{
			leftDistance = rightDistance = 0.5;
		}

		factor = leftDistance / ( leftDistance + rightDistance );
	}


	struct AffectFrameReal : public AffectFrame
	{
		AffectFrameReal()
			: val( 0.f )
		{

		}

		Real	val;
	};

	struct AffectFrameVector2 : public AffectFrame
	{
		AffectFrameVector2()
			: val( Vector2::ZERO )
		{

		}

		Vector2	val;

	};

	struct AffectFrameVector3 : public AffectFrame
	{
		AffectFrameVector3()
			: val( Vector3::ZERO )
		{

		}

		Vector3	val;
	};



	struct AffectorReal
	{
		AffectorReal()
			: pos( 0.f )
			, duration( 0.f )
			, interpolateVal( 0.f )
		{

		}

		~AffectorReal()
		{
			MapKeyFrame::iterator iter = frames.begin();
			MapKeyFrame::iterator iterEnd = frames.end();

			while ( iter != iterEnd )
			{
				delete iter->second;

				++iter;
			}
		}

		void	update( Real timeLapse, bool loop )
		{
			pos += timeLapse;

			if ( pos > duration )
			{
				if ( loop )
				{
					pos = 0.f;
				}
				else
				{
					pos = duration;

				}
			}


			AffectFrame* _left = 0;
			AffectFrame* _right = 0;

			Real factor = 0.f;

			find2NeighbouringKeyframe( frames, pos, _left, _right, factor );

			AffectFrameReal* left = static_cast< AffectFrameReal* >( _left );
			AffectFrameReal* right = static_cast< AffectFrameReal* >( _right );

			interpolateVal = left->val * ( 1.0f - factor ) + right->val * factor;
		}

		
		Real			interpolateVal;
		Real			pos;
		Real			duration;
		MapKeyFrame		frames;
	};

	struct AffectorVector2
	{
		AffectorVector2()
			: pos( 0.f )
			, duration( 0.f )
			, interpolateVal( Vector2::ZERO )
		{

		}

		~AffectorVector2()
		{
			MapKeyFrame::iterator iter = frames.begin();
			MapKeyFrame::iterator iterEnd = frames.end();

			while ( iter != iterEnd )
			{
				delete iter->second;

				++iter;
			}
		}

		void	update( Real timeLapse, bool loop )
		{
			pos += timeLapse;

			if ( pos > duration )
			{
				if ( loop )
				{
					pos = 0.f;
				}
				else
				{
					pos = duration;

				}
			}


			AffectFrame* _left = 0;
			AffectFrame* _right = 0;

			Real factor = 0.f;

			find2NeighbouringKeyframe( frames, pos, _left, _right, factor );

			AffectFrameVector2* left = static_cast< AffectFrameVector2* >( _left );
			AffectFrameVector2* right = static_cast< AffectFrameVector2* >( _right );

			interpolateVal = left->val * ( 1.0f - factor ) + right->val * factor;
		}

		Vector2			interpolateVal;
		Real			pos;
		Real			duration;
		MapKeyFrame		frames;
	};

	struct AffectorVector3
	{
		AffectorVector3()
			: pos( 0.f )
			, duration( 0.f )
			, interpolateVal( Vector3::ZERO )
		{

		}

		~AffectorVector3()
		{
			MapKeyFrame::iterator iter = frames.begin();
			MapKeyFrame::iterator iterEnd = frames.end();

			while ( iter != iterEnd )
			{
				delete iter->second;

				++iter;
			}
		}

		void	update( Real timeLapse, bool loop )
		{
			pos += timeLapse;

			if ( pos > duration )
			{
				if ( loop )
				{
					pos = 0.f;
				}
				else
				{
					pos = duration;

				}
			}

			AffectFrame* _left = 0;
			AffectFrame* _right = 0;

			Real factor = 0.f;

			find2NeighbouringKeyframe( frames, pos, _left, _right, factor );

			AffectFrameVector3* left = static_cast< AffectFrameVector3* >( _left );
			AffectFrameVector3* right = static_cast< AffectFrameVector3* >( _right );

			interpolateVal = left->val * ( 1.0f - factor ) + right->val * factor;
		
		}

		Vector3			interpolateVal;
		Real			pos;
		Real			duration;
		MapKeyFrame		frames;
	};

	struct ActionDescEffectUpdate : public ActionDesc
	{
		ActionDescEffectUpdate() 
		{

		}

		~ActionDescEffectUpdate()
		{
		}

		MapTimeReal			alpha;

		MapTimeReal			rot;

		MapTimeVector2		scale;

		MapTimeVector2		pos;

		MapTimeVector3		colorAdd;

		MapTimeVector3		colorMuti;
	};

	//---
	ActionEffectUpdate::ActionEffectUpdate( Actor* owner, ActionDesc* desc )
	: Action( desc, owner )
	{
		mActorEffect = static_cast< ActorEffect* >( owner );
		
		ActionDescEffectUpdate* descEffect = static_cast< ActionDescEffectUpdate* >( desc );

		if ( descEffect->alpha.empty() == false )
		{
			mAlpha = new AffectorReal;

			MapTimeReal::iterator iter = descEffect->alpha.begin();
			MapTimeReal::iterator iterEnd = descEffect->alpha.end();

			while ( iter != iterEnd )
			{
				AffectFrameReal* frame = new AffectFrameReal;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mAlpha->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mAlpha->duration < frame->timePos )
				{
					mAlpha->duration = frame->timePos;
				}

				++iter;
			}

		}

		if ( descEffect->rot.empty() == false )
		{
			mRot = new AffectorReal;

			MapTimeReal::iterator iter = descEffect->rot.begin();
			MapTimeReal::iterator iterEnd = descEffect->rot.end();

			while ( iter != iterEnd )
			{
				AffectFrameReal* frame = new AffectFrameReal;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mRot->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mRot->duration < frame->timePos )
				{
					mRot->duration = frame->timePos;
				}

				++iter;
			}
		}

		if ( descEffect->scale.empty() == false )
		{
			mScale = new AffectorVector2;

			MapTimeVector2::iterator iter = descEffect->scale.begin();
			MapTimeVector2::iterator iterEnd = descEffect->scale.end();

			while ( iter != iterEnd )
			{
				AffectFrameVector2* frame = new AffectFrameVector2;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mScale->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mScale->duration < frame->timePos )
				{
					mScale->duration = frame->timePos;
				}

				++iter;
			}
		}

		if ( descEffect->pos.empty() == false )
		{
			mPos = new AffectorVector2;

			MapTimeVector2::iterator iter = descEffect->pos.begin();
			MapTimeVector2::iterator iterEnd = descEffect->pos.end();

			while ( iter != iterEnd )
			{
				AffectFrameVector2* frame = new AffectFrameVector2;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mPos->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mPos->duration < frame->timePos )
				{
					mPos->duration = frame->timePos;
				}

				++iter;
			}
		}

		if ( descEffect->colorAdd.empty() == false )
		{
			mColorAdd = new AffectorVector3;

			MapTimeVector3::iterator iter = descEffect->colorAdd.begin();
			MapTimeVector3::iterator iterEnd = descEffect->colorAdd.end();

			while ( iter != iterEnd )
			{
				AffectFrameVector3* frame = new AffectFrameVector3;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mColorAdd->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mColorAdd->duration < frame->timePos )
				{
					mColorAdd->duration = frame->timePos;
				}

				++iter;
			}
		}

		if ( descEffect->colorMuti.empty() == false )
		{
			mColorMuti = new AffectorVector3;

			MapTimeVector3::iterator iter = descEffect->colorMuti.begin();
			MapTimeVector3::iterator iterEnd = descEffect->colorMuti.end();

			while ( iter != iterEnd )
			{
				AffectFrameVector3* frame = new AffectFrameVector3;
				frame->timePos = iter->first;
				frame->val = iter->second;

				mColorMuti->frames.insert( MapKeyFrame::value_type( frame->timePos, frame ) );

				if ( mColorMuti->duration < frame->timePos )
				{
					mColorMuti->duration = frame->timePos;
				}

				++iter;
			}
		}
	}

	ActionEffectUpdate::~ActionEffectUpdate()
	{
		SafeDelete( mAlpha );
		SafeDelete( mRot );
		SafeDelete( mScale );
		SafeDelete( mPos );
		SafeDelete( mColorAdd );
		SafeDelete( mColorMuti );
	}

	void	ActionEffectUpdate::initailze()
	{

	}

	const String&	ActionEffectUpdate::type() const
	{
		return ActionFactoryEffectUpdate::TypeName;
	}

	void	ActionEffectUpdate::begin()
	{
		Action::begin();

		
	}

	void	ActionEffectUpdate::end()
	{
	
		Action::end();
	}

	void	ActionEffectUpdate::update( Real timelapse )
	{
		bool loop = mActorEffect->isLoop();

		if ( loop == false )
		{
			mLifeTimeLapse += timelapse;

			if ( mLifeTimeLapse >= mLifeTime )
			{
				mActorEffect->valid();
			}
		}
		
		if ( mAlpha )
		{
			mAlpha->update( timelapse, loop );

			mActorEffect->setProperty( "alpha", Any( mAlpha->interpolateVal ) );
		}

		if ( mRot )
		{
			mRot->update( timelapse, loop );

			mActorEffect->setProperty( "rot", Any( mRot->interpolateVal ) );
		}

		if ( mPos )
		{
			mPos->update( timelapse, loop );

			mActorEffect->setProperty( "posOff", Any( mPos->interpolateVal ) );
		}

		if ( mScale )
		{
			mScale->update( timelapse, loop );

			mActorEffect->setProperty( "scale", Any( mScale->interpolateVal ) );
		}

		if ( mColorAdd )
		{
			mColorAdd->update( timelapse, loop );

			mActorEffect->setProperty( "colorAdd", Any( mColorAdd->interpolateVal ) );
		}

		if ( mColorMuti )
		{
			mColorMuti->update( timelapse, loop );

			mActorEffect->setProperty( "colorMuti", Any( mColorMuti->interpolateVal ) );
		}

	}

	//---
	const String ActionFactoryEffectUpdate::TypeName = "Update";
	ActionFactoryEffectUpdate::ActionFactoryEffectUpdate()
	{

	}

	ActionFactoryEffectUpdate::~ActionFactoryEffectUpdate()
	{

	}

	const String&	ActionFactoryEffectUpdate::type() const
	{

		return TypeName;
	}

	Action*	ActionFactoryEffectUpdate::createInstance( Actor* owner, ActionDesc* desc )
	{
		ActionEffectUpdate* action = new ActionEffectUpdate( owner, desc );
		
		return action;
	}

	ActionDesc*	ActionFactoryEffectUpdate::load( rapidxml::xml_node<>* xmlNode, const String& filename )
	{
		using namespace rapidxml;

		xml_attribute<>* nodeAttr = 0;

		ActionDescEffectUpdate* actionDesc = new ActionDescEffectUpdate;

		_loadBaseActionDesc( actionDesc, xmlNode, filename );

		xml_node<>*  xmlNodeAffectors = xmlNode->first_node( "affector" );
		if ( xmlNodeAffectors )
		{
			//-- alpha
			xml_node<>* xmlNodeAffectorAlpha = xmlNodeAffectors->first_node( "alpha" );

			if ( xmlNodeAffectorAlpha )
			{
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorAlpha->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );


					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Real val = StringConverter::parseReal( nodeAttr->value() );

					actionDesc->alpha.insert( MapTimeReal::value_type( timePos, val ) );


					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}


			//-- rot
			xml_node<>* xmlNodeAffectorRot = xmlNodeAffectors->first_node( "rot" );

			if ( xmlNodeAffectorRot )
			{	
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorRot->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );
					
					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );

					
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Real val = StringConverter::parseReal( nodeAttr->value() );

					actionDesc->rot.insert( MapTimeReal::value_type( timePos, val ) );

					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}

			//-- pos
			xml_node<>* xmlNodeAffectorPos = xmlNodeAffectors->first_node( "pos" );

			if ( xmlNodeAffectorPos )
			{
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorPos->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );


					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Vector2 val = StringConverter::parseVector2( nodeAttr->value() );

					actionDesc->pos.insert( MapTimeVector2::value_type( timePos, val ) );

					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}

			//-- scale
			xml_node<>* xmlNodeAffectorScale = xmlNodeAffectors->first_node( "scale" );

			if ( xmlNodeAffectorScale )
			{
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorScale->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );


					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Vector2 val = StringConverter::parseVector2( nodeAttr->value() );

					actionDesc->scale.insert( MapTimeVector2::value_type( timePos, val ) );

					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}

			//-- colorAdd
			xml_node<>* xmlNodeAffectorColorAdd = xmlNodeAffectors->first_node( "colorAdd" );

			if ( xmlNodeAffectorColorAdd )
			{
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorColorAdd->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );


					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Vector3 val = StringConverter::parseVector3( nodeAttr->value() );

					actionDesc->colorAdd.insert( MapTimeVector3::value_type( timePos, val ) );

					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}

			//-- colorMuti
			xml_node<>* xmlNodeAffectorColorMuti = xmlNodeAffectors->first_node( "colorMuti" );

			if ( xmlNodeAffectorColorMuti )
			{
				xml_node<>* xmlNodeAffectorFrame = xmlNodeAffectorColorMuti->first_node( "frame" );

				if ( xmlNodeAffectorFrame == 0 )
				{
					EXCEPTEX( "effect actor. uddate action. rot affector need frame label. filename: " << filename );
				}

				while ( xmlNodeAffectorFrame )
				{
					nodeAttr = xmlNodeAffectorFrame->first_attribute( "pos" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need pos label. filename: " << filename );
					}

					Real timePos = StringConverter::parseReal( nodeAttr->value() );


					nodeAttr = xmlNodeAffectorFrame->first_attribute( "val" );

					if ( nodeAttr == 0 )
					{
						EXCEPTEX( "effect actor. uddate action. frame need val label. filename: " << filename );
					}

					Vector3 val = StringConverter::parseVector3( nodeAttr->value() );

					actionDesc->colorMuti.insert( MapTimeVector3::value_type( timePos, val ) );

					if ( timePos > actionDesc->lifeTime )
					{
						actionDesc->lifeTime = timePos;
					}

					xmlNodeAffectorFrame = xmlNodeAffectorFrame->next_sibling();
				}

			}
			
		}

		
		return actionDesc;
	}

}