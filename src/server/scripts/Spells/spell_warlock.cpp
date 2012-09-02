/*
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008 - 2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "ScriptPCH.h"
#include "Spell.h"
#include "SpellAuraEffects.h"

enum WarlockSpells {
	WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS = 54435,
	WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER = 54443,
	WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD = 54508,
	WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER = 54509,
	WARLOCK_DEMONIC_EMPOWERMENT_IMP = 54444,
	//WARLOCK_IMPROVED_HEALTHSTONE_R1         = 18692,
	//WARLOCK_IMPROVED_HEALTHSTONE_R2         = 18693,
	WARLOCK_FELHUNTER_SHADOWBITE_R1 = 54049
};

//71521 spell_warl_Hand_of_Guldan
class spell_warl_Hand_of_Guldan: public SpellScriptLoader 
{
public:
    spell_warl_Hand_of_Guldan() : SpellScriptLoader("spell_warl_Hand_of_Guldan") 
    {}

    class spell_warl_Hand_of_Guldan_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_Hand_of_Guldan_SpellScript)

        void BeforeEffect(SpellEffIndex /*effIndex*/) 
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (!caster)
                return;

            //Cast the debuff on the target (it applies the aura)
            caster->CastSpell(target, 86000, true);

            //Cast also the roots if the warlock has the talent
            if(AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 140, 0))
            {
                if(aurEff->GetId() == 89604)
                    //Rank 1
                    caster->CastSpell(target, 93974, true);
                else
                    //Rank 2
                    caster->CastSpell(target, 93987, true);
            }

            //Check the aura not the auraEffect because the aura effect of the Hand of Gul'dan is not applied on the targets. It's is on the ground, they just get the debuff (aura)
            if(target->HasAura(86000, caster->GetGUID()))
            {
                Aura *aur = target->GetAura(86000, caster->GetGUID());
                //Get the AuraEffect object from the aura
                AuraEffect *aurEff = aur->GetEffect(EFFECT_0);
                std::list<Unit*> targets;

                //Get the targets that took the Hand of Gul'dan's debuff at the beginning (for the stun if they remain in the 4 yard range for 6 sec)
                aurEff->GetTargetList(targets);

                //Set the instance variable for the targets stun check
                aurEff->SetUnitList(targets);
            }
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_warl_Hand_of_Guldan_SpellScript::BeforeEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_Hand_of_Guldan_SpellScript();
    }
};

//1490 spell_warl_curse_of_the_elements
class spell_warl_curse_of_the_elements: public SpellScriptLoader 
{
public:
    spell_warl_curse_of_the_elements() : SpellScriptLoader("spell_warl_curse_of_the_elements") 
    {}

    class spell_warl_curse_of_the_elements_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_curse_of_the_elements_SpellScript)

        void HandleScriptEffect(SpellEffIndex /*effIndex*/) 
        {
            //It needs the caster in order to localize the right debuff when there are more then one on the same target
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!target)
                return;

            if (!caster)
                return;
            
            //If there is the Curse of the Elements set the duration of Jinx
            if (caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 5002,0))
            {
                //Id of the jinx to cast, depending on the talents the warlock has
                uint32 jinxRankSpellId;

                //Check if warlock has the either the first or the second rank of jinx
                if(caster->HasAura(85479))
                    jinxRankSpellId = 86105;
                else if (caster->HasAura(18179))
                    jinxRankSpellId = 85547;

                //Cast Jinx
                caster->CastSpell(target, jinxRankSpellId, true);

                //Start the periodic tick
                if(AuraEffect* aurEff = target->GetAuraEffect(jinxRankSpellId, caster->GetGUID()))
                {
                    aurEff->SetPeriodicTimer(1000);
                    aurEff->SetPeriodic(true);
                }
            }   
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_warl_curse_of_the_elements_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_curse_of_the_elements_SpellScript();
    }
};

// 47193 Demonic Empowerment
class spell_warl_demonic_empowerment: public SpellScriptLoader {
public:
	spell_warl_demonic_empowerment() :
			SpellScriptLoader("spell_warl_demonic_empowerment") {
	}

	class spell_warl_demonic_empowerment_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_demonic_empowerment_SpellScript)
		bool Validate(SpellEntry const * /*spellEntry*/) {
			if (!sSpellStore.LookupEntry(WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS))
				return false;
			if (!sSpellStore.LookupEntry(
					WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER))
				return false;
			if (!sSpellStore.LookupEntry(WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD))
				return false;
			if (!sSpellStore.LookupEntry(WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER))
				return false;
			if (!sSpellStore.LookupEntry(WARLOCK_DEMONIC_EMPOWERMENT_IMP))
				return false;
			return true;
		}

		void HandleScriptEffect(SpellEffIndex /*effIndex*/) {
			if (Creature* targetCreature = GetHitCreature()) {
				if (targetCreature->isPet()) {
					CreatureInfo const * ci = ObjectMgr::GetCreatureTemplate(
							targetCreature->GetEntry());
					switch (ci->family) {
					case CREATURE_FAMILY_SUCCUBUS:
						targetCreature->CastSpell(targetCreature,
								WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS, true);
						break;
					case CREATURE_FAMILY_VOIDWALKER: {
						SpellEntry const* spellInfo = sSpellStore.LookupEntry(
								WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER);
						int32 hp = int32(
								targetCreature->CountPctFromMaxHealth(
										GetCaster()->CalculateSpellDamage(
												targetCreature, spellInfo, 0)));
						targetCreature->CastCustomSpell(targetCreature,
								WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER, &hp,
								NULL, NULL, true);
						//unitTarget->CastSpell(unitTarget, 54441, true);
						break;
					}
					case CREATURE_FAMILY_FELGUARD:
						targetCreature->CastSpell(targetCreature,
								WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD, true);
						break;
					case CREATURE_FAMILY_FELHUNTER:
						targetCreature->CastSpell(targetCreature,
								WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER, true);
						break;
					case CREATURE_FAMILY_IMP:
						targetCreature->CastSpell(targetCreature,
								WARLOCK_DEMONIC_EMPOWERMENT_IMP, true);
						break;
					}
				}
			}
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_warl_demonic_empowerment_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warl_demonic_empowerment_SpellScript();
	}
};

// 47422 Everlasting Affliction
class spell_warl_everlasting_affliction: public SpellScriptLoader {
public:
	spell_warl_everlasting_affliction() :
			SpellScriptLoader("spell_warl_everlasting_affliction") {
	}

	class spell_warl_everlasting_affliction_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_everlasting_affliction_SpellScript)
		void HandleScriptEffect(SpellEffIndex /*effIndex*/) {
			if (Unit* unitTarget = GetHitUnit())
				// Refresh corruption on target
				if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0x2, 0, 0, GetCaster()->GetGUID()))
					aur->GetBase()->RefreshDuration();
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_warl_everlasting_affliction_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warl_everlasting_affliction_SpellScript();
	}
};

// 6201 Create Healthstone (and ranks)
class spell_warl_create_healthstone: public SpellScriptLoader {
public:
	spell_warl_create_healthstone() :
			SpellScriptLoader("spell_warl_create_healthstone") {
	}

	class spell_warl_create_healthstone_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_create_healthstone_SpellScript)
		static uint32 const iTypes[8][3];

		void HandleScriptEffect(SpellEffIndex effIndex) {
			if (Unit* unitTarget = GetHitUnit()) {
				uint32 rank = 0;

				uint8 spellRank = sSpellMgr->GetSpellRank(GetSpellInfo()->Id);
				if (spellRank > 0 && spellRank <= 8)
					CreateItem(effIndex, iTypes[spellRank - 1][rank]);
			}
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_warl_create_healthstone_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warl_create_healthstone_SpellScript();
	}
};

uint32 const spell_warl_create_healthstone::spell_warl_create_healthstone_SpellScript::iTypes[8][3] =
		{ { 5512, 19004, 19005 }, // Minor Healthstone
				{ 5511, 19006, 19007 }, // Lesser Healthstone
				{ 5509, 19008, 19009 }, // Healthstone
				{ 5510, 19010, 19011 }, // Greater Healthstone
				{ 9421, 19012, 19013 }, // Major Healthstone
				{ 22103, 22104, 22105 }, // Master Healthstone
				{ 36889, 36890, 36891 }, // Demonic Healthstone
				{ 36892, 36893, 36894 } // Fel Healthstone
		};

// 1120 Drain Soul
 class spell_warl_drain_soul: public SpellScriptLoader 
 {
 public:
    spell_warl_drain_soul() : SpellScriptLoader("spell_warl_drain_soul") { }

    class spell_warl_drain_soul_AuraScript: public AuraScript {
        PrepareAuraScript(spell_warl_drain_soul_AuraScript)

        void OnPeriodic(AuraEffect const* /*aurEff*/)
        {
            // Pandemic
            if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 4554, 1))
            {
                SpellEntry const* spellproto = aurEff->GetSpellProto();
                if (GetTarget()->HealthBelowPct(25))
                    if (roll_chance_i(spellproto->EffectBasePoints[0]))
                        if (AuraEffect* aur = GetTarget()->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0, 0x100, 0, GetCaster()->GetGUID()))
                           aur->GetBase()->RefreshDuration();
            }
         }

        void OnRemove(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = aurEff->GetBase()->GetCaster())
                if (!GetTarget()->isAlive())
                    caster->CastSpell(caster, 79264, true);
        }

        void Register() {
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_soul_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_soul_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const {
        return new spell_warl_drain_soul_AuraScript();
    }
};


//80398 Dark Intent
class spell_warlock_dark_intent: public SpellScriptLoader {
public:
	spell_warlock_dark_intent() :
			SpellScriptLoader("spell_warlock_dark_intent") {
	}

	class spell_warlock_dark_intent_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warlock_dark_intent_SpellScript)

		void HandleScriptEffect(SpellEffIndex effIndex) {
			Unit* caster = GetCaster();
			Unit* target = GetHitUnit();

			if (!caster || !target)
				return;

            //Save the target
            caster->setDarkIntentTargets(target);
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_warlock_dark_intent_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warlock_dark_intent_SpellScript();
	}
};

class spell_warl_immolate: public SpellScriptLoader {
public:
	spell_warl_immolate() :
			SpellScriptLoader("spell_warl_immolate") {
	}

	class spell_warl_immolate_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_immolate_SpellScript)

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return true;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/) {
			if (Unit * caster = GetCaster()) {
				if (caster->GetTypeId() != TYPEID_PLAYER)
					return;

				caster->ToPlayer()->KilledMonsterCredit(44175, 0);
			}
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_warl_immolate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warl_immolate_SpellScript();
	}
};

//27285 Seed of Corruption
class spell_warl_seed_of_corruption: public SpellScriptLoader {
public:
	spell_warl_seed_of_corruption() :
			SpellScriptLoader("spell_warl_seed_of_corruption") {
	}

	class spell_warl_seed_of_corruption_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_seed_of_corruption_SpellScript)
		;

		void FilterTargets(std::list<Unit*>& unitList) {
			unitList.remove(GetTargetUnit());
		}

		void Register() {
			OnUnitTargetSelect +=
					SpellUnitTargetFn(spell_warl_seed_of_corruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_AREA_ENEMY_DST);
		}
	};

	SpellScript *GetSpellScript() const {
		return new spell_warl_seed_of_corruption_SpellScript();
	}
};

// 54049 Shadow Bite
class spell_warl_shadow_bite: public SpellScriptLoader {
public:
	spell_warl_shadow_bite() :
			SpellScriptLoader("spell_warl_shadow_bite") {
	}

	class spell_warl_shadow_bite_SpellScript: public SpellScript {
		PrepareSpellScript(spell_warl_shadow_bite_SpellScript)
		bool Validate(SpellEntry const * /*spellEntry*/) {
			if (!sSpellStore.LookupEntry(WARLOCK_FELHUNTER_SHADOWBITE_R1))
				return false;
			return true;
		}

		void HandleScriptEffect(SpellEffIndex /*effIndex*/) {
			//Unit *caster = GetCaster();
			// Get DoTs on target by owner (15% increase by dot)
			// need to get this here from SpellEffects.cpp ?
			//damage *= float(100.f + 15.f * caster->getVictim()->GetDoTsByCaster(caster->GetOwnerGUID())) / 100.f;
		}

		// Improved Felhunter parts commented--deprecated. removed in cataclysm
		// For Improved Felhunter
		void HandleAfterHitEffect() {
			Unit *caster = GetCaster();
			if (!caster) {
				return;
			};

			// break if our caster is not a pet
			if (!(caster->GetTypeId() == TYPEID_UNIT
					&& caster->ToCreature()->isPet())) {
				return;
			};

			// break if pet has no owner and/or owner is not a player
			Unit *owner = caster->GetOwner();
			if (!(owner && (owner->GetTypeId() == TYPEID_PLAYER))) {
				return;
			};

			/*int32 amount;
			 // rank 1 - 4%
			 if(owner->HasAura(WARLOCK_IMPROVED_FELHUNTER_R1)) { amount = 5; };*/

			/*// rank 2 - 8%
			 if(owner->HasAura(WARLOCK_IMPROVED_FELHUNTER_R2)) { amount = 9; };*/

			// Finally return the Mana to our Caster
			/*if(AuraEffect * aurEff = owner->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 214, 0))
			 caster->CastCustomSpell(caster,WARLOCK_IMPROVED_FELHUNTER_EFFECT,&amount,NULL,NULL,true,NULL,aurEff,caster->GetGUID());*/
		}

		void Register() {
			//OnEffect += SpellEffectFn(spell_warl_shadow_bite_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
			AfterHit +=
					SpellHitFn(spell_warl_shadow_bite_SpellScript::HandleAfterHitEffect);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_warl_shadow_bite_SpellScript();
	}
};
//DrainLife fix: thnks to rebase. fixed by wlasser
class spell_warl_drain_life: public SpellScriptLoader {
public:
	spell_warl_drain_life() :
			SpellScriptLoader("spell_warl_drain_life") {
	}
	class spell_warl_drain_life_AuraScript: public AuraScript {
		PrepareAuraScript(spell_warl_drain_life_AuraScript)
		;
		void OnPeriodic(AuraEffect const* /*aurEff*/) {
			int32 bp = 2; // Normal, restore 2% of health
			// Check for Death's Embrace
			if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 3223, 0))
				if (GetCaster()->HealthBelowPct(25))
					bp += int32(aurEff->GetAmount());
			GetCaster()->CastCustomSpell(GetCaster(), 89653, &bp, NULL, NULL,
					true);
		}
		void Register() {
			OnEffectPeriodic +=
					AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
		}
	};
	AuraScript* GetAuraScript() const {
		return new spell_warl_drain_life_AuraScript();
	}
};

class spell_soul_swap_buff : public SpellScriptLoader
{
    public:
        spell_soul_swap_buff() : SpellScriptLoader("spell_soul_swap_buff") { }

        class spell_soul_swap_buffAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_soul_swap_buffAuraScript)

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes mode)
            {
                Unit * target = GetTarget();
                Unit * caster = GetCaster();

                if (!caster)
                    return;

                caster->ResetSoulSwapDots();
            }

            // function registering
            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_soul_swap_buffAuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_332_REPLACE_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript *GetAuraScript() const
        {
            return new spell_soul_swap_buffAuraScript();
        }
};

//86121 Soul Swap
class spell_warl_soul_swap: public SpellScriptLoader {
public:
        spell_warl_soul_swap() : SpellScriptLoader("spell_warl_soul_swap") { }

        class spell_warl_soul_swap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_swap_SpellScript)

            SpellCastResult CheckRequirement()
            {
                if (Unit* caster = GetTargetUnit()) 
                {
                    //Check if there are any dots on the target
                    if(caster->GetSoulSwapDotsCount() == 0)
                        return SPELL_FAILED_BAD_TARGETS;
                }

                return SPELL_CAST_OK;
            }
            
            void BeforeEffect(SpellEffIndex /*effIndex*/) 
            {
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!target)
                    return;

                if (!caster)
                    return;

                target->CastSpell(caster, 92795, true, 0, 0, caster->GetGUID());
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_soul_swap_SpellScript::CheckRequirement);
                OnEffect += SpellEffectFn(spell_warl_soul_swap_SpellScript::BeforeEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_warl_soul_swap_SpellScript();
        }
};

class spell_soul_swap_exhale : public SpellScriptLoader
{
    public:
        spell_soul_swap_exhale() : SpellScriptLoader("spell_soul_swap_exhale") { }

        class spell_soul_swap_exhaleSpellScript : public SpellScript
        {
            PrepareSpellScript(spell_soul_swap_exhaleSpellScript)

            SpellCastResult CheckRequirementInternal(SpellCustomErrors& extendedError)
            {
                return SPELL_CAST_OK;
            }

            SpellCastResult CheckRequirement()
            {
                if (!GetTargetUnit())
                    return SPELL_FAILED_BAD_TARGETS;

                if (GetTargetUnit()->GetGUID() == GetCaster()->GetSourceOfSoulSwapDots())
                    return SPELL_FAILED_BAD_TARGETS;

                SpellCustomErrors extension = SPELL_CUSTOM_ERROR_NONE;
                SpellCastResult result = CheckRequirementInternal(extension);

                if (result != SPELL_CAST_OK)
                {
                    Spell::SendCastResult(GetTargetUnit()->ToPlayer(), GetSpellInfo(), 0, result, extension);
                    return result;
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_soul_swap_exhaleSpellScript::CheckRequirement);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_soul_swap_exhaleSpellScript();
        }
};
// spell_warl_fel_flame
class spell_warl_fel_flame: public SpellScriptLoader 
{
public:
    spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") {
    }

    class spell_warl_fel_flame_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_fel_flame_SpellScript)

        void HandleScriptEffect(SpellEffIndex /*effIndex*/) 
        {
            Unit* target = GetHitUnit();
            Unit* caster = GetCaster();

            if (!target)
                return;

            if (!caster)
                return;
            
            if (target->HasAura(348, caster->GetGUID()))
            {
                int32 newDuration = target->GetAura(348, caster->GetGUID())->GetDuration();
                if (newDuration >= GetEffectValue()*1000)
                    newDuration = target->GetAura(348, caster->GetGUID())->GetMaxDuration();
                else
                    newDuration += (GetEffectValue()*1000);

                target->GetAura(348, caster->GetGUID())->SetDuration(newDuration, true);
            } else if (target->HasAura(30108, caster->GetGUID()))
            {
                int32 newDuration = target->GetAura(30108, caster->GetGUID())->GetDuration();
                if (newDuration >= GetEffectValue()*1000)
                    newDuration = target->GetAura(30108, caster->GetGUID())->GetMaxDuration();
                else
                    newDuration += (GetEffectValue()*1000);

                target->GetAura(30108, caster->GetGUID())->SetDuration(newDuration, true);
            }            
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_warl_fel_flame_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_fel_flame_SpellScript();
    }
};

// soul link
class spell_warl_soul_link : public SpellScriptLoader
{
public:
    spell_warl_soul_link() : SpellScriptLoader("spell_warl_soul_link")
    { }

    class spell_warl_soul_link_SpellScript: public SpellScript 
    {
        PrepareSpellScript(spell_warl_soul_link_SpellScript)

        void HandleScriptEffect(SpellEffIndex effIndex) 
        {
            if (Unit* pet = GetHitUnit()) 
            {
                pet->CastSpell(pet, 25228, true);
            }
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_warl_soul_link_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_soul_link_SpellScript();
    }
};

// soulburn demonic circle teleport
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
public:
    spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") {
    }

    class spell_warl_demonic_circle_teleport_SpellScript: public SpellScript 
    {
        PrepareSpellScript(spell_warl_demonic_circle_teleport_SpellScript)

        void HandleScriptEffect(SpellEffIndex effIndex) 
        {
            if (Unit* caster = GetHitUnit()) 
            {
                if (caster->HasAura(74434))
                {
                    caster->CastSpell(caster, 79438, true);
                    caster->RemoveAura(74434);
                }
            }
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_warl_demonic_circle_teleport_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_demonic_circle_teleport_SpellScript();
    }
};

class spell_warlock_seduction : public SpellScriptLoader 
{
public:
	spell_warlock_seduction() : SpellScriptLoader("spell_warlock_seduction") 
    { }

	class spell_warlock_seduction_SpellScript: public SpellScript 
    {
		PrepareSpellScript(spell_warlock_seduction_SpellScript)

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
			if (Unit *unitTarget = GetHitUnit())
            {
                // Glyph of Blind
                if (GetCaster()->GetOwner())
                {
                    if (GetCaster()->GetOwner()->HasAura(56250))
                    {
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409)); // SW:D shall not be removed.
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                        unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                    }
                }
            }

		}

		void Register()
        {
			OnEffect += SpellEffectFn(spell_warlock_seduction_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
		}
	};

	SpellScript* GetSpellScript() const 
    {
		return new spell_warlock_seduction_SpellScript();
	}
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_Hand_of_Guldan();
    new spell_warl_curse_of_the_elements();
	new spell_warl_demonic_empowerment();
	new spell_warl_everlasting_affliction();
	new spell_warl_create_healthstone();
	new spell_warl_drain_soul();
	new spell_warlock_dark_intent();
	new spell_warl_immolate();
	new spell_warl_seed_of_corruption();
	new spell_warl_shadow_bite();
	new spell_warl_drain_life();
    new spell_soul_swap_buff();
    new spell_warl_soul_swap();
    new spell_soul_swap_exhale();
    new spell_warl_fel_flame();
    new spell_warl_soul_link();
    new spell_warl_demonic_circle_teleport();
    new spell_warlock_seduction();
}
