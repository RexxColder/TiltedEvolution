#include <TiltedOnlinePCH.h>

#include <BSAnimationGraphManager.h>
#include <Havok/BShkbAnimationGraph.h>
#include <Havok/BShkbHkxDB.h>
#include <Havok/hkbBehaviorGraph.h>

#include <TiltedCore/Hash.hpp>

#if TP_FALLOUT4

uint64_t BSAnimationGraphManager::GetDescriptorKey(int aForceIndex)
{
    using TiltedPhoques::FHash::Crc64;

    String variableNames{};
    variableNames.reserve(8192);
    std::map<uint32_t, const char*> variables;

    if (animationGraphIndex < animationGraphs.size)
    {
        const auto pGraph = aForceIndex == -1 ? animationGraphs.Get(animationGraphIndex) : animationGraphs.Get(aForceIndex);

        if (pGraph)
        {
            const auto pDb = pGraph->hkxDB;
            if (pDb)
            {
                const auto pBuckets = pDb->animationVariables.buckets;
                const auto pVariableSet = pGraph->behaviorGraph ? pGraph->behaviorGraph->animationVariables : nullptr;

                if (pBuckets && pVariableSet)
                {
                    for (decltype(pDb->animationVariables.bucketCount) i = 0; i < pDb->animationVariables.bucketCount; ++i)
                    {
                        auto pBucket = &pBuckets[i];
                        if (!pBucket->next)
                            continue;

                        while (pBucket != pDb->animationVariables.end)
                        {
                            const auto variableIndex = pBucket->value;
                            if (pVariableSet->size > static_cast<uint32_t>(variableIndex))
                            {
                                variables[variableIndex] = pBucket->key.AsAscii();
                            }

                            pBucket = pBucket->next;
                        }
                    }

                    for (auto& [id, name] : variables)
                    {
                        variableNames += name;
                    }
                }
            }
        }
    }

    std::transform(variableNames.begin(), variableNames.end(), variableNames.begin(), [](unsigned char c) { return std::tolower(c); });

    return Crc64(reinterpret_cast<const unsigned char*>(variableNames.c_str()), variableNames.size());
}

#endif
